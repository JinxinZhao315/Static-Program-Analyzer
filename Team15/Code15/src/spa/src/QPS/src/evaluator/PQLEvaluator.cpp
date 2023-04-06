#include "QPS/include/evaluator/PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB &pkb)
{
    this->pkb = pkb;
}

std::set<std::string> PQLEvaluator::evaluate(Query query)
{
    SelectClause* selectClause = query.getSelectClause();
    std::vector<Elem*> selectedElems = selectClause->getSelectedElements();

    std::vector<Clause*> clauseList = query.getClauseList();
    std::vector<std::string> synUsageSequence;
    for (Clause *clause : clauseList) {
        std::vector<std::string> usedSyns = clause->getSynList();
        synUsageSequence.insert(synUsageSequence.end(), usedSyns.begin(), usedSyns.end());
    }
    bool isEarlyExit = false;
    ResultTable resultTable = ResultTable();
    std::multimap<std::string, std::string> synonymTable = query.getSynonymTable();
    int currSynEvalPos = 0;
    for (Clause *clause : clauseList) {
        evalClause(clause, isEarlyExit, synonymTable, resultTable, synUsageSequence, currSynEvalPos);
        if (isEarlyExit) {
            break;
        }
    }
    
    set<std::string> retSet = resultTable.getSelectedResult(selectedElems, pkb, isEarlyExit);

    return retSet;
}

//ResultTable PQLEvaluator::evalGroup(ClauseEvalGroup group, bool& isEarlyExit,
//    std::multimap<std::string, std::string>synonymTable, std::vector<std::string>selectedElemName) {
//    std::vector<Clause*> clauseList = group.getClauseList();
//    std::vector<std::string> synList = group.getSynList();
//    synList.insert(synList.end(), selectedElemName.begin(), selectedElemName.end());
//    ResultTable intermediateTable = ResultTable();
//    int clauseArgVecIndex = 0;
//    for (Clause* clause : clauseList) {
//        if (isEarlyExit) break;
//        switch (clause->getType())
//        {
//        case SUCH_THAT: {
//            SuchThatClause* suchThatCl = static_cast<SuchThatClause*>(clause);
//            std::string relationship = suchThatCl->getRelationShip();
//
//            SuchThatHandler suchThatHandler(pkb);
//            Result result = suchThatHandler.evaluate(Utility::getRelationshipFromString(relationship),
//                *suchThatCl, intermediateTable, synonymTable, clauseArgVecIndex, synList);
//
//            if (!result.isResultTrue()) {
//                isEarlyExit = true;
//                break;
//            }
//            //intermediateTable.combineTable(result.getClauseResult());
//            // there used to be some syns in the table but now it is empty
//            //if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
//            //    isEarlyExit = true;
//            //    break;
//            //}
//            // no such arg left in the following clause, can delete it in resultTable
//            //std::vector<std::string> usedSyns = suchThatCl->getSynList();
//            //for (int i = 0; i < usedSyns.size(); i++) {
//            //    if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
//            //        intermediateTable.deleteSynonym(usedSyns[i]);
//            //    }
//            //    clauseArgVecIndex++;
//            //}
//
//            break;
//        }
//        case WITH: {
//            WithClause* withCl = static_cast<WithClause*>(clause);
//            WithHandler withHandler = WithHandler(pkb);
//
//            Result result = withHandler.evaluate(*withCl, intermediateTable, synonymTable);
//            if (!result.isResultTrue()) {
//                isEarlyExit = true;
//                break;
//            }
//
//            intermediateTable.combineTable(result.getClauseResult());
//            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
//                isEarlyExit = true;
//                break;
//            }
//
//            std::vector<std::string> usedSyns = withCl->getSynList();
//            for (int i = 0; i < usedSyns.size(); i++) {
//                if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
//                    intermediateTable.deleteSynonym(usedSyns[i]);
//                }
//                clauseArgVecIndex++;
//            }
//            break;
//        }
//        case PATTERN: {
//            PatternClause* patternCl = static_cast<PatternClause*>(clause);
//            PatternHandler patternHandler = PatternHandler(pkb);
//
//            Result result = patternHandler.evaluate(*patternCl, intermediateTable, synonymTable);
//
//            if (!result.isResultTrue()) {
//                isEarlyExit = true;
//                break;
//            }
//
//            intermediateTable.combineTable(result.getClauseResult());
//            if (intermediateTable.isTableEmpty() && !intermediateTable.isSynListEmpty()) {
//                isEarlyExit = true;
//                break;
//            }
//            std::vector<std::string> usedSyns = patternCl->getSynList();
//            for (int i = 0; i < usedSyns.size(); i++) {
//                if (!Utility::isSynUsedLater(synList, clauseArgVecIndex)) {
//                    intermediateTable.deleteSynonym(usedSyns[i]);
//                }
//                clauseArgVecIndex++;
//            }
//            break;
//        }
//        default:
//            break;
//        }
//    }
//    return intermediateTable;
//}

void PQLEvaluator::evalClause(Clause* clause, bool& isEarlyExit, 
    std::multimap<std::string, std::string> synonymTable, ResultTable& resultTable,
    std::vector<std::string> synUsageSequence, int& currSynEvalPos) {
    if (isEarlyExit) return;
    switch (clause->getType())
    {
    case SUCH_THAT: {
        SuchThatClause* suchThatCl = static_cast<SuchThatClause*>(clause);
        std::string relationship = suchThatCl->getRelationShip();

        SuchThatHandler suchThatHandler(pkb);
        Result result = suchThatHandler.evaluate(Utility::getRelationshipFromString(relationship),
            *suchThatCl, resultTable, synonymTable, currSynEvalPos, synUsageSequence);

        if (!result.isResultTrue()) {
            isEarlyExit = true;
            break;
        }

        break;
    }
    case WITH: {
        WithClause* withCl = static_cast<WithClause*>(clause);
        WithHandler withHandler = WithHandler(pkb);

        Result result = withHandler.evaluate(*withCl, resultTable, synonymTable);
        if (!result.isResultTrue()) {
            isEarlyExit = true;
            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            isEarlyExit = true;
            break;
        }

        std::vector<std::string> usedSyns = withCl->getSynList();
        for (int i = 0; i < usedSyns.size(); i++) {
            if (!Utility::isSynUsedLater(synUsageSequence, currSynEvalPos)) {
                resultTable.deleteSynonym(usedSyns[i]);
            }
            currSynEvalPos++;
        }
        break;
    }
    case PATTERN: {
        PatternClause* patternCl = static_cast<PatternClause*>(clause);
        PatternHandler patternHandler = PatternHandler(pkb);

        Result result = patternHandler.evaluate(*patternCl, resultTable, synonymTable);

        if (!result.isResultTrue()) {
            isEarlyExit = true;
            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            isEarlyExit = true;
            break;
        }
        std::vector<std::string> usedSyns = patternCl->getSynList();
        for (int i = 0; i < usedSyns.size(); i++) {
            if (!Utility::isSynUsedLater(synUsageSequence, currSynEvalPos)) {
                resultTable.deleteSynonym(usedSyns[i]);
            }
            currSynEvalPos++;
        }
        break;
    }
    case SELECT: {
        SelectClause* selectCl = static_cast<SelectClause*>(clause);
        SelectHandler selectHandler = SelectHandler(pkb);
        selectHandler.evaluate(*selectCl, synonymTable, resultTable);
        break;
    }
    default:
        break;
    }
}