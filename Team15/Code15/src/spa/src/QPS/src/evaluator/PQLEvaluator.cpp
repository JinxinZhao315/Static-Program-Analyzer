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

    for (Elem e : selectedElems)
    {
        selectedElemName.push_back(e.getSynName());
    }

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        clauseArgVec.push_back(suchThatCl.getLeftArg());
        clauseArgVec.push_back(suchThatCl.getRightArg());
    }

    for (PatternClause &patternCl : patternVec)
    {
        clauseArgVec.push_back(patternCl.getPatternSynonym());
        clauseArgVec.push_back(patternCl.getFirstArg());
        clauseArgVec.push_back(patternCl.getSecondArg());
        clauseArgVec.push_back(patternCl.getThirdArg());
    }

    for (WithClause &withCl : withVec)
    {
        clauseArgVec.push_back(withCl.getFirstArgStr());
        clauseArgVec.push_back(withCl.getSecondArgStr());
    }

    // selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        std::string relationship = suchThatCl.getRelationShip();

        SuchThatHandler suchThatHandler(pkb);
        Result result = suchThatHandler.evaluate(Utility::getRelationshipFromString(relationship),
                                                 suchThatCl,
                                                 synonymTable);

        if (!result.isResultTrue())
        {

            resultTable.clearResultTable();

            isEarlyExit = true;

            break;
        }
        resultTable.combineTable(result.getClauseResult());
        // there used to be some syns in the table but now it is empty
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty())
        {

            isEarlyExit = true;

            break;
        }
        // no such arg left in the following clause, can delete it in resultTable
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(suchThatCl.getLeftArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(suchThatCl.getRightArg());
        }
        clauseArgVecIndex++;
    }

    for (PatternClause &patternCl : patternVec)
    {
        if (isEarlyExit)
        {
            break;
        }
        PatternHandler patternHandler = PatternHandler(pkb);

        Result result = patternHandler.evaluate(patternCl, resultTable, synonymTable);

        if (!result.isResultTrue())
        {
            isEarlyExit = true;

            resultTable.clearResultTable();
            isEarlyExit = true;
            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty())
        {
            isEarlyExit = true;
            break;
        }

        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(patternCl.getPatternSynonym());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(patternCl.getFirstArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(patternCl.getSecondArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(patternCl.getThirdArg());
        }
        clauseArgVecIndex++;
    }

    for (WithClause &withCl : withVec)
    {
        if (isEarlyExit)
        {
            break;
        }
        WithHandler withHandler = WithHandler(pkb);

        Result result = withHandler.evaluate(withCl, resultTable, synonymTable);
        if (!result.isResultTrue())
        {
            isEarlyExit = true;
            resultTable.clearResultTable();
            isEarlyExit = true;
            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty())
        {
            isEarlyExit = true;
            break;
        }

        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(withCl.getFirstArgStr());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex))
        {
            resultTable.deleteSynonym(withCl.getSecondArgStr());
        }
        clauseArgVecIndex++;
    }

    selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    set<std::string> retSet = resultTable.getSelectedResult(selectedElems, pkb, isEarlyExit);

    return retSet;
}


bool PQLEvaluator::isArgUsedLater(std::vector<std::string> selectedSyn, std::vector<std::string> argList, int currArgPos)
{
    std::string argName = argList[currArgPos];
    auto argNextOccur = std::find(argList.begin() + currArgPos + 1, argList.end(), argName);
    bool isArgSelected = std::find(selectedSyn.begin(), selectedSyn.end(), argName) != selectedSyn.end();
    if (argNextOccur == argList.end() && !isArgSelected)
    {
        return false;
    }
    else
    {
        return true;
    }
}

ResultTable PQLEvaluator::evalGroup(ClauseEvalGroup group, bool& isEarlyExit,
    std::multimap<std::string, std::string>synonymTable, std::vector<std::string>selectedElemName) {
    std::vector<Clause*> clauseList = group.getClauseList();
    std::vector<std::string> synList = group.getSynList();
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
                *suchThatCl, synonymTable);

            if (!result.isResultTrue())
            {
                intermediateTable.clearResultTable();
                isEarlyExit = true;
                break;
            }
            intermediateTable.combineTable(result.getClauseResult());
            // there used to be some syns in the table but now it is empty
            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
                isEarlyExit = true;
                break;
            }
            // no such arg left in the following clause, can delete it in resultTable
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(suchThatCl->getLeftArg());
            }
            clauseArgVecIndex++;
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(suchThatCl->getRightArg());
            }
            clauseArgVecIndex++;
        }
        case WITH: {
            WithClause* withCl = static_cast<WithClause*>(clause);
            WithHandler withHandler = WithHandler(pkb);

            Result result = withHandler.evaluate(*withCl, intermediateTable, synonymTable);
            if (!result.isResultTrue())
            {
                isEarlyExit = true;
                intermediateTable.clearResultTable();
                break;
            }

            intermediateTable.combineTable(result.getClauseResult());
            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty())
            {
                isEarlyExit = true;
                break;
            }

            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(withCl->getFirstArgStr());
            }
            clauseArgVecIndex++;
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(withCl->getSecondArgStr());
            }
            clauseArgVecIndex++;
        }
        case PATTERN: {
            PatternClause* patternCl = static_cast<PatternClause*>(clause);
            PatternHandler patternHandler = PatternHandler(pkb);

            Result result = patternHandler.evaluate(*patternCl, intermediateTable, synonymTable);

            if (!result.isResultTrue())
            {
                isEarlyExit = true;
                intermediateTable.clearResultTable();
                break;
            }

            intermediateTable.combineTable(result.getClauseResult());
            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty())
            {
                isEarlyExit = true;
                break;
            }

            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(patternCl->getPatternSynonym());
            }
            clauseArgVecIndex++;
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(patternCl->getFirstArg());
            }
            clauseArgVecIndex++;
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(patternCl->getSecondArg());
            }
            clauseArgVecIndex++;
            if (!isArgUsedLater(selectedElemName, synList, clauseArgVecIndex))
            {
                intermediateTable.deleteSynonym(patternCl->getThirdArg());
            }
            clauseArgVecIndex++;
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
        std::set<std::string> clauseSynList(clauseList[i]->getSynList().begin(), clauseList[i]->getSynList().end());
        clauseToSynMap.insert(std::make_pair<>(i, clauseSynList));
        clauseListIntRep.insert(i);
        //there will be maximum 2 syn
        if (clauseSynList.size() == 2) {
            std::string firstSyn = *clauseSynList.begin();
            std::string secondSyn = *clauseSynList.end();

            synToSynConnectionMap[firstSyn].insert(secondSyn);
            synToSynConnectionMap[secondSyn].insert(firstSyn);
        }
        for (std::string syn : clauseSynList) {
            synToClauseMap[syn].insert(i);
            //if (synToClauseMap.count(syn)) {
            //    synToClauseMap[syn].insert();
            //}
        }
    }

    while (clauseListIntRep.size() > 0) {
        auto firstClauseNum = clauseListIntRep.begin();
        clauseListIntRep.erase(firstClauseNum);
        std::set<std::string> synList = clauseToSynMap.at(*firstClauseNum);
        //group with single syn
        if (synList.size() == 0) {
            ClauseEvalGroup subGroup;
            subGroup.addClause(clauseList[*firstClauseNum]);
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