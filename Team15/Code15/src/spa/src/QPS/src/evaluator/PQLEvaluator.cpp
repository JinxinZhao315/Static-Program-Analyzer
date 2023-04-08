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

        if (!result.isResultTrue() || (resultTable.isTableEmpty() && !resultTable.isSynListEmpty())) {
            isEarlyExit = true;
            break;
        }

        break;
    }
    case WITH: {
        WithClause* withCl = static_cast<WithClause*>(clause);
        WithHandler withHandler = WithHandler(pkb);

        Result result = withHandler.evaluate(*withCl, resultTable, synonymTable, currSynEvalPos, synUsageSequence);
        if (!result.isResultTrue() || (resultTable.isTableEmpty() && !resultTable.isSynListEmpty())) {
            isEarlyExit = true;
            break;
        }
        break;
    }
    case PATTERN: {
        PatternClause* patternCl = static_cast<PatternClause*>(clause);
        PatternHandler patternHandler = PatternHandler(pkb);

        Result result = patternHandler.evaluate(*patternCl, resultTable, synonymTable, currSynEvalPos, synUsageSequence);

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