#include "QPS/include/evaluator/PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB &pkb)
{
    this->pkb = pkb;
}

std::string PQLEvaluator::evaluate(Query query)
{
    ResultTable resultTable = ResultTable();
    std::multimap<std::string, std::string> synonymTable = query.getSynonymTable();
    SelectHandler selectHandler = SelectHandler(pkb);


    std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternVec = query.getPatternClauseVec();


    //todo make clauseHandler.evaluate instead of if else branch

    bool isEarlyExit = false;

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        std::string relationship = suchThatCl.getRelationShip();
        if (relationship == "Follows" || relationship == "Follows*")
        {
            FollowsHandler followsHandler = FollowsHandler(pkb);
            bool isStar = relationship == "Follows" ? false : true;
            Result result = followsHandler.evalFollows(isStar, suchThatCl, resultTable, synonymTable);
            if (result.isResultTrue() == false)
            {

                resultTable.resetKeySetEmpty(selectedVarName);

                isEarlyExit = true;

                break;
            }
            followsHandler.combineResult(resultTable, result);
        }
        /*else if (relationship == "Uses") 
        {
            UsesHandler usesHandler = UsesHandler(pkb);
            Result result = usesHandler.evalUses(suchThatCl, resultTable, varTable);
            if (result.isResultTrue() == false) {
                resultTable.deleteKeyValuePair(selectedVarName);
                resultTable.insertKeyValuePair(selectedVarName, {});
                isEarlyExit = true;
                break;
            }
            usesHandler.combineResult(resultTable, result);
        }*/

       if (relationship == "Parent" || relationship == "Parent*") {
            ParentHandler parentHandler = ParentHandler(pkb);
            bool isStar = relationship == "Parent" ? false : true;
            Result result = parentHandler.evalParentStar(isStar, suchThatCl, resultTable, synonymTable);
            if (result.isResultTrue() == false)
            {

                resultTable.resetKeySetEmpty(selectedVarName);

                isEarlyExit = true;

                break;
            }
            parentHandler.combineResult(resultTable, result);
        }
        if (relationship == "Modifies") {
            Result result;

            std::string leftArg = suchThatCl.getLeftArg();
            std::string leftType = Utility::getReferenceType(leftArg);
            //ModifiesPHandler modifiesPHandler = ModifiesPHandler(pkb);
            ModifiesSHandler modifiesSHandler = ModifiesSHandler(pkb);

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure") ) {
                //modifiesPHandler = ModifiesPHandler(pkb);
                //result = modifiesPHandler.evalModifiesP(suchThatCl, resultTable, synonymTable);
            }
            else {
 
                result = modifiesSHandler.evalModifiesS(suchThatCl, resultTable, synonymTable);
            }


            if (result.isResultTrue() == false)
            {

                resultTable.resetKeySetEmpty(selectedVarName);

                isEarlyExit = true;

                break;
            }

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
                //modifiesPHandler.combineResult(resultTable, result);
            }
            else {
                modifiesSHandler.combineResult(resultTable, result);
            }

        }
    }
    for (PatternClause patternCl : patternVec)
    {
        if (isEarlyExit) {
            break;
        }
        PatternHandler patternHandler = PatternHandler(pkb);

        Result result = patternHandler.evalPattern(patternCl, resultTable, synonymTable);

        if (result.isResultTrue() == false)
        {
//            resultTable.deleteKeyValuePair(selectedVarName);
//            resultTable.insertKeyValuePair(selectedVarName, {});
            isEarlyExit = true;
            break;
        }

        patternHandler.combineResult(resultTable, result);
    }

    // return the values of the selected synonym in ResultTable
    std::string retStr;
    set<string> retSet = resultTable.getStringSetFromKey(selectedVarName);
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
