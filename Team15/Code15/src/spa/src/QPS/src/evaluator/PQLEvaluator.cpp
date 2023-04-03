#include "QPS/include/evaluator/PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB &pkb)
{
    this->pkb = pkb;
}

std::set<std::string> PQLEvaluator::evaluate(Query query)
{
    ResultTable resultTable = ResultTable();
    std::multimap<std::string, std::string> synonymTable = query.getSynonymTable();
    SelectHandler selectHandler = SelectHandler(pkb);
    std::vector<Elem> selectedElems = query.getSelectClause().getSynNameVec();
    std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternVec = query.getPatternClauseVec();
    std::vector<WithClause> withVec = query.getWithClauseVec();

    bool isEarlyExit = false;

    std::vector<std::string> selectedElemName;
    std::vector<std::string> clauseArgVec;
    int clauseArgVecIndex = 0;
    ClauseEvalGroup originEvalGroup;

    for (Elem e : selectedElems)
    {
        selectedElemName.push_back(e.getSynName());
    }

    for (int i = 0; i < suchThatVec.size(); i++) {
        originEvalGroup.addClause(&suchThatVec[i]);
    }

    for (int i = 0; i < patternVec.size(); i++) {
        originEvalGroup.addClause(&patternVec[i]);
    }

    for (int i = 0; i < withVec.size(); i++) {
        originEvalGroup.addClause(&withVec[i]);
    }

    std::vector<ClauseEvalGroup> clauseEvalGroups = separateEvalGroup(originEvalGroup);
    for (ClauseEvalGroup group : clauseEvalGroups) {
        ResultTable tempTable = evalGroup(group, isEarlyExit, synonymTable, selectedElemName);
        if (isEarlyExit) {
            break;
        }
        //only selected Elem will be combined in resultTable
        resultTable.combineTable(tempTable);
    }

    if (!isEarlyExit) {
        selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name
    }
    

    set<std::string> retSet = resultTable.getSelectedResult(selectedElems, pkb, isEarlyExit);

    return retSet;
}

ResultTable PQLEvaluator::evalGroup(ClauseEvalGroup group, bool& isEarlyExit,
    std::multimap<std::string, std::string>synonymTable, std::vector<std::string>selectedElemName) {
    std::vector<Clause*> clauseList = group.getClauseList();
    std::vector<std::string> synList = group.getSynList();
    synList.insert(synList.end(), selectedElemName.begin(), selectedElemName.end());
    ResultTable intermediateTable = ResultTable();
    int clauseArgVecIndex = 0;
    for (Clause* clause : clauseList) {
        if (isEarlyExit == true) break;
        switch (clause->getType())
        {
        case SUCH_THAT: {
            SuchThatClause* suchThatCl = static_cast<SuchThatClause*>(clause);
            std::string relationship = suchThatCl->getRelationShip();

            SuchThatHandler suchThatHandler(pkb);
            Result result = suchThatHandler.evaluate(Utility::getRelationshipFromString(relationship),
                *suchThatCl, intermediateTable, synonymTable, clauseArgVecIndex, synList);

            if (!result.isResultTrue()) {
                isEarlyExit = true;
                break;
            }
            //intermediateTable.combineTable(result.getClauseResult());
            // there used to be some syns in the table but now it is empty
            //if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
            //    isEarlyExit = true;
            //    break;
            //}
            // no such arg left in the following clause, can delete it in resultTable
            //std::vector<std::string> usedSyns = suchThatCl->getSynList();
            //for (int i = 0; i < usedSyns.size(); i++) {
            //    if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
            //        intermediateTable.deleteSynonym(usedSyns[i]);
            //    }
            //    clauseArgVecIndex++;
            //}
            break;
        }
        case WITH: {
            WithClause* withCl = static_cast<WithClause*>(clause);
            WithHandler withHandler = WithHandler(pkb);

            Result result = withHandler.evaluate(*withCl, intermediateTable, synonymTable);
            if (!result.isResultTrue()) {
                isEarlyExit = true;
                break;
            }

            intermediateTable.combineTable(result.getClauseResult());
            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
                isEarlyExit = true;
                break;
            }

            std::vector<std::string> usedSyns = withCl->getSynList();
            for (int i = 0; i < usedSyns.size(); i++) {
                if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
                    intermediateTable.deleteSynonym(usedSyns[i]);
                }
                clauseArgVecIndex++;
            }
            break;
        }
        case PATTERN: {
            PatternClause* patternCl = static_cast<PatternClause*>(clause);
            PatternHandler patternHandler = PatternHandler(pkb);

            Result result = patternHandler.evaluate(*patternCl, intermediateTable, synonymTable);

            if (!result.isResultTrue()) {
                isEarlyExit = true;
                break;
            }

            intermediateTable.combineTable(result.getClauseResult());
            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
                isEarlyExit = true;
                break;
            }
            std::vector<std::string> usedSyns = patternCl->getSynList();
            for (int i = 0; i < usedSyns.size(); i++) {
                if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
                    intermediateTable.deleteSynonym(usedSyns[i]);
                }
                clauseArgVecIndex++;
            }
            break;
        }
        default:
            break;
        }
    }
    return intermediateTable;
}

std::vector<ClauseEvalGroup> PQLEvaluator::separateEvalGroup(ClauseEvalGroup group) {
    std::vector<Clause*> clauseList = group.getClauseList();
    std::set<int> clauseListIntRep;
    std::unordered_map<int, std::set<std::string>> clauseToSynMap;
    std::unordered_map<std::string, std::set<int>> synToClauseMap;
    std::unordered_map<std::string, std::set<std::string>> synToSynConnectionMap;
    std::vector<ClauseEvalGroup> groupWithoutSyn;
    std::vector<ClauseEvalGroup> groupWithSyn;
    //construct 2 hashmap
    for (int i = 0; i < clauseList.size(); i++) {
        std::vector<std::string> clauseSynVec = clauseList[i]->getSynList();
        std::set<std::string> clauseSynList(clauseSynVec.begin(), clauseSynVec.end());
        clauseToSynMap.insert(std::make_pair<>(i, clauseSynList));
        clauseListIntRep.insert(i);
        //there will be maximum 2 syn
        switch (clauseSynList.size())
        {
        case 1: {
            std::set<std::string>::iterator it = clauseSynList.begin();
            std::string firstSyn = *it;
            synToSynConnectionMap[firstSyn] = std::set<std::string>();
            break;
        }
        case 2: {
            std::set<std::string>::iterator it = clauseSynList.begin();
            std::string firstSyn = *it;
            it++;
            std::string secondSyn = *(it);

            synToSynConnectionMap[firstSyn].insert(secondSyn);
            synToSynConnectionMap[secondSyn].insert(firstSyn);
            break;
        }
        default:
            break;
        }
        for (std::string syn : clauseSynList) {
            synToClauseMap[syn].insert(i);
        }
    }

    while (clauseListIntRep.size() > 0) {
        auto firstClauseIter = clauseListIntRep.begin();
        int firstClauseNum = *firstClauseIter;
        clauseListIntRep.erase(firstClauseNum);
        std::set<std::string> synList = clauseToSynMap.at(firstClauseNum);
        //group with single syn
        if (synList.size() == 0) {
            ClauseEvalGroup subGroup;
            subGroup.addClause(clauseList[firstClauseNum]);
            groupWithoutSyn.push_back(subGroup);
            continue;
        }
        std::set<std::string> visitedSynList;
        std::set<int> currGroupClauses;
        //BFS to traverse the syn connection graph, result syn stored in visitedSynList, currGroupClauses will also be filled
        while (synList.size() > 0) {
            std::set<std::string> tempSynList;
            for (std::string syn : synList) {
                //syn not visited yet
                if (visitedSynList.count(syn) == 0) {
                    std::set<int> relatedClauses = synToClauseMap.at(syn);
                    currGroupClauses.insert(relatedClauses.begin(), relatedClauses.end());
                    //find all the connected syn and add the syn in tempSynList
                    std::set<std::string> relatedSyns = synToSynConnectionMap.at(syn);
                    for (std::string relatedSyn : relatedSyns) {
                        tempSynList.insert(relatedSyn);
                    }
                }
                visitedSynList.insert(syn);
            }
            synList = tempSynList;
        }
        ClauseEvalGroup subGroup;
        for (int i : currGroupClauses) {
            subGroup.addClause(clauseList[i]);
            clauseListIntRep.erase(i);
        }
        groupWithSyn.push_back(subGroup);
    }
    std::vector<ClauseEvalGroup> result = groupWithoutSyn;
    result.insert(std::end(result), std::begin(groupWithSyn), std::end(groupWithSyn));
    return result;
}