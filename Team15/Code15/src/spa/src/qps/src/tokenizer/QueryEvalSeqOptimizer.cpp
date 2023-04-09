#include"qps/include/tokenizer/QueryEvalSeqOptimizer.h"

QueryEvalSeqOptimizer::QueryEvalSeqOptimizer() {};

void QueryEvalSeqOptimizer::optimizeEvalSeq(Query& query) {
    SelectClause* selectClause = query.getSelectClause();
    std::vector<Elem*> selectedElems = selectClause->getSelectedElements();
    std::vector<std::string> selectedSyn;
    for (Elem* e : selectedElems) {
        selectedSyn.push_back(e->getSynName());
    }
    std::vector<Clause*> clauseList = query.getClauseList();
    //pop the select clause out
    clauseList.pop_back();
    std::unordered_map<int, std::set<int>> clauseToClauseMap = constructGraph(clauseList);
    std::vector<std::vector<int>> evalGroups = seperateEvalGroup(clauseList, clauseToClauseMap, selectedSyn);

    std::vector<Clause*> finalEvalSeq;
    for (std::vector<int> evalGroup : evalGroups) {
        std::vector<int> orderedEvalGroup = evalGroup;
        if (evalGroup.size() > 1) {
           orderedEvalGroup = generateOrderedEvalGroup(clauseList, evalGroup, clauseToClauseMap);   
        }
        for (int clauseIntRep : orderedEvalGroup) {
            finalEvalSeq.push_back(clauseList[clauseIntRep]);
        }
    }
    finalEvalSeq.push_back(selectClause);
    query.setClauseList(finalEvalSeq);
}

std::unordered_map<int, std::set<int>> QueryEvalSeqOptimizer::constructGraph(std::vector<Clause*> clauseList) {
    std::unordered_map<int, std::set<int>> clauseToClauseMap;
    std::unordered_map<std::string, std::set<int>> synToClauseMap;
    //construct synToClauseMap
    for (int i = 0; i < clauseList.size(); i++) {
        std::vector<std::string> clauseSynVec = clauseList[i]->getSynList();
        std::set<std::string> clauseSynList(clauseSynVec.begin(), clauseSynVec.end());
        for (std::string syn : clauseSynList) {
            synToClauseMap[syn].insert(i);
        }
    }
    for (auto synIter = synToClauseMap.begin(); synIter != synToClauseMap.end(); synIter++) {
        std::set<int> relatedClause = synIter->second;
        for (int clauseNum : relatedClause) {
            //add all the connected clauses but remove itself from it
            clauseToClauseMap[clauseNum].insert(relatedClause.begin(), relatedClause.end());
            clauseToClauseMap[clauseNum].erase(clauseNum);
        }
    }
    return clauseToClauseMap;
}

std::vector<std::vector<int>> QueryEvalSeqOptimizer::seperateEvalGroup(std::vector<Clause*> clauseList,
    std::unordered_map<int, std::set<int>> clauseToClauseMap, std::vector<std::string> selectedSynName) {
    std::set<int> originClauseSet;
    for (int clauseIntRep = 0; clauseIntRep < clauseList.size(); clauseIntRep++) {
        originClauseSet.insert(clauseIntRep);
    }
    std::vector<std::vector<int>> groupWithoutSyn;
    std::vector<std::vector<int>> groupWithNoSelectedSyn;
    std::vector<std::vector<int>> groupWithSelectedSyn;

    //construct multiple eval groups
    while (!originClauseSet.empty()) {
        int firstClauseNum = *originClauseSet.begin();
        originClauseSet.erase(firstClauseNum);
        std::vector<std::string> usedSyns = clauseList[firstClauseNum]->getSynList();
        //group with no syn
        if (usedSyns.empty()) {
            std::vector<int> subGroup;
            subGroup.push_back(firstClauseNum);
            groupWithoutSyn.push_back(subGroup);
            continue;
        }
        std::set<int> visitedClauses;
        std::set<int> currGroupClauses = { firstClauseNum };
        bool isSelectedSynInClause = false;
        //BFS to traverse the clause connection graph, result clause stored in visitedClauses, currGroupClauses will also be filled
        while (!currGroupClauses.empty()) {
            std::set<int> tempClauseList;
            for (int clauseIntRep : currGroupClauses) {
                //clause not visited yet
                if (visitedClauses.count(clauseIntRep) == 0) {
                    //check if there is an syn in clause that is selected
                    std::vector<std::string> synList = clauseList[clauseIntRep]->getSynList();
                    for (std::string syn : synList) {
                        if (std::find(selectedSynName.begin(), selectedSynName.end(), syn) != selectedSynName.end()) {
                            isSelectedSynInClause = true;
                        }
                    }
                    std::set<int> relatedClauses = clauseToClauseMap.at(clauseIntRep);
                    tempClauseList.insert(relatedClauses.begin(), relatedClauses.end());
                    visitedClauses.insert(clauseIntRep);
                }
            }
            currGroupClauses = tempClauseList;
        }
        std::vector<int> subGroup;
        for (int clauseIntRep : visitedClauses) {
            subGroup.push_back(clauseIntRep);
            originClauseSet.erase(clauseIntRep);
        }
        if (isSelectedSynInClause) {
            groupWithSelectedSyn.push_back(subGroup);
        }
        else {
            groupWithNoSelectedSyn.push_back(subGroup);
        }
    }
    std::vector<std::vector<int>> result = groupWithoutSyn;
    result.insert(std::end(result), std::begin(groupWithSelectedSyn), std::end(groupWithSelectedSyn));
    result.insert(std::end(result), std::begin(groupWithNoSelectedSyn), std::end(groupWithNoSelectedSyn));
    return result;
}

std::vector<int> QueryEvalSeqOptimizer::generateOrderedEvalGroup(std::vector<Clause*> clauseList, std::vector<int> evalGroup,
    std::unordered_map<int, std::set<int>> clauseToClauseMap) {
    //find the clause with the highest priority in current group as a starting point for BFS
    int highestPriorityClause = 0;
    for (int clauseIntRep : evalGroup) {
        PriorityLevel currPriorityLevel = getPriority(clauseList[clauseIntRep]);
        PriorityLevel highestPriorityLevel = getPriority(clauseList[highestPriorityClause]);
        if (currPriorityLevel < highestPriorityLevel) {
            highestPriorityClause = clauseIntRep;
        }
    }

    //push the clause with the highest priority to pq with pair(clauseIntRep, priorityLevel)
    priority_queue<pair<int, PriorityLevel>, std::vector<pair<int, PriorityLevel>>, decltype(&Utility::comparator)> pq(&Utility::comparator);
    pq.push(std::make_pair<>(highestPriorityClause, getPriority(clauseList[highestPriorityClause])));
    std::vector<int> visitedClause;

    //start BFS
    while (pq.size() > 0) {
        priority_queue<pair<int, PriorityLevel>, std::vector<pair<int, PriorityLevel>>, decltype(&Utility::comparator)> tempPq(&Utility::comparator);
        while (pq.size() > 0) {
            int clauseIntRep = pq.top().first;
            pq.pop();
            if (std::find(visitedClause.begin(), visitedClause.end(), clauseIntRep) == visitedClause.end()) {
                visitedClause.push_back(clauseIntRep);
                for (int connectedClause : clauseToClauseMap.at(clauseIntRep)) {
                    tempPq.push(std::make_pair(connectedClause, getPriority(clauseList[connectedClause])));
                }
            }
        }
        pq = tempPq;
    }

    //visitedClause is already ordered by the sequence in BFS
    return visitedClause;
}

PriorityLevel QueryEvalSeqOptimizer::getPriority(Clause* clause) {
    std::set<Relationship> simpleRelationship = { FOLLOWS, PARENT, CALLS, USES, USES_S, USES_P, MODIFIES, MODIFIES_S, MODIFIES_P, NEXT };
    std::set<Relationship> mediumRelationship = { FOLLOWS_STAR, PARENT_STAR, CALLS_STAR };
    std::set<Relationship> complexRelationship = { NEXT_STAR, AFFECTS, AFFECTS_STAR };
    if (clause->getType() == WITH && clause->getSynList().size() == 1) {
        return ZERO;
    }
    //pattern clause with 1 syn
    else if (clause->getType() == PATTERN && clause->getSynList().size() == 1) {
        return ONE;
    }
    //suchthat clause with 1 syn: simple(3), medium(4), complex(9)
    else if (clause->getType() == SUCH_THAT && clause->getSynList().size() == 1) {
        std::string relationship = (static_cast<SuchThatClause*>(clause))->getRelationShip();
        if (simpleRelationship.count(Utility::getRelationshipFromString(relationship)) > 0) {
            return TWO;
        }
        else if (mediumRelationship.count(Utility::getRelationshipFromString(relationship)) > 0) {
            return THREE;
        }
        else {
            return EIGHT;
        }
    }
    //with clause with 2 syns
    else if (clause->getType() == WITH && clause->getSynList().size() == 2) {
        return FOUR;
    }
    //pattern clause with 2 syns
    else if (clause->getType() == PATTERN && clause->getSynList().size() == 2) {
        return FIVE;
    }
    //suchthat clause with 2 syns: simple(7), medium(8), complex(10)
    //if (clause->getType() == SUCH_THAT && clause->getSynList().size() == 2) 
    else {
        std::string relationship = (static_cast<SuchThatClause*>(clause))->getRelationShip();
        if (simpleRelationship.count(Utility::getRelationshipFromString(relationship)) > 0) {
            return SIX;
        }
        else if (mediumRelationship.count(Utility::getRelationshipFromString(relationship)) > 0) {
            return SEVEN;
        }
        else {
            return NINE;
        }
    }
}