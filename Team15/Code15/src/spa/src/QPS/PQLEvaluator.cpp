#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB &pkb)
{
    this->pkb = pkb;
}

std::string PQLEvaluator::evaluate(Query query)
{
    ResultTable resultTable = ResultTable();

    std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    SelectHandler selectHandler = SelectHandler(pkb);
    std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable); // update resultTable and return the synonym name

    std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternVec = query.getPatternClauseVec();

    bool isEarlyExit = false;

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        std::string relationship = suchThatCl.getRelationShip();
        if (relationship == "Follows" || relationship == "Follows*")
        {
            FollowsHandler followsHandler = FollowsHandler(pkb);
            bool isStar = relationship == "Follows" ? false : true;
            Result result = followsHandler.evalFollows(isStar, suchThatCl, resultTable, varTable);
            if (result.isResultTrue() == false)
            {
                resultTable.deleteKeyValuePair(selectedVarName);
                resultTable.insertKeyValuePair(selectedVarName, {});
                isEarlyExit = true;
                break;
            }
            followsHandler.combineResult(resultTable, result);
        }

    }

    for (PatternClause patternCl : patternVec)
    {
        if (isEarlyExit) {
            break;
        }
        PatternHandler patternHandler = PatternHandler(pkb);
        Result result = patternHandler.evalPattern(patternCl, resultTable, varTable);
        if (result.isResultTrue() == false)
        {
            resultTable.deleteKeyValuePair(selectedVarName);
            resultTable.insertKeyValuePair(selectedVarName, {});
            isEarlyExit = true;
            break;
        }
        patternHandler.combineResult(resultTable, result);
    }

    // return the values of the selected synonym in ResultTable
    std::string retStr;
    set<string> retSet = resultTable.getValueFromKey(selectedVarName);
    if (retSet.empty())
    {
        retStr = "None";
    }
    else
    {
        retStr = std::accumulate(begin(retSet),
                                 end(retSet),
                                 string{},
                                 [](const string &a, const string &b)
                                 { return a.empty() ? b : a + ',' + b; });
    }

    return retStr;
}
