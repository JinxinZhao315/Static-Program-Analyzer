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

                resultTable.clearResultTable();

                isEarlyExit = true;

                break;
            }
            resultTable.combineTable(result.getClauseResult());
            if (resultTable.isTableEmpty()) {

                isEarlyExit = true;

                break;
            }
        }

       else if (relationship == "Parent" || relationship == "Parent*") {
            ParentHandler parentHandler = ParentHandler(pkb);
            bool isStar = relationship == "Parent" ? false : true;
            Result result = parentHandler.evalParentStar(isStar, suchThatCl, resultTable, synonymTable);
            if (result.isResultTrue() == false)
            {

                resultTable.clearResultTable();

                isEarlyExit = true;

                break;
            }
            resultTable.combineTable(result.getClauseResult());
            if (resultTable.isTableEmpty()) {

                isEarlyExit = true;

                break;
            }
        }
        else if (relationship == "Modifies") {
            Result result;

            std::string leftArg = suchThatCl.getLeftArg();
            std::string leftType = Utility::getReferenceType(leftArg);
            ModifiesPHandler modifiesPHandler = ModifiesPHandler(pkb);
            ModifiesSHandler modifiesSHandler = ModifiesSHandler(pkb);

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure") ) {
                result = modifiesPHandler.evalModifiesP(suchThatCl, resultTable, synonymTable);
            }
            else {
                result = modifiesSHandler.evalModifiesS(suchThatCl, resultTable, synonymTable);
            }


            if (result.isResultTrue() == false)
            {

                resultTable.clearResultTable();

                isEarlyExit = true;

                break;
            }
            else {
                resultTable.combineTable(result.getClauseResult());
            }

            if (resultTable.isTableEmpty()) {

                isEarlyExit = true;

                break;
            }

        }
        else if (relationship == "Uses") {
            Result result;

            std::string leftArg = suchThatCl.getLeftArg();
            std::string leftType = Utility::getReferenceType(leftArg);
            UsesPHandler usesPHandler = UsesPHandler(pkb);
            UsesSHandler usesSHandler = UsesSHandler(pkb);

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
                result = usesPHandler.evalUsesP(suchThatCl, resultTable, synonymTable);
            }
            else {

                result = usesSHandler.evalUsesS(suchThatCl, resultTable, synonymTable);
            }


            if (result.isResultTrue() == false)
            {

                resultTable.clearResultTable();

                isEarlyExit = true;

                break;
            }
            else {
                resultTable.combineTable(result.getClauseResult());
            }

            if (resultTable.isTableEmpty()) {

                isEarlyExit = true;

                break;
            }
        }
        /*else if (relationship == "Calls" || relationship == "Calls*") {

            CallsHandler callsHandler = CallsHandler(pkb);
            bool isStar = relationship == "Calls" ? false : true;
            Result result = callsHandler.evalCalls(isStar, suchThatCl, resultTable, synonymTable);
            if (result.isResultTrue() == false)
            {

                resultTable.clearResultTable();

                isEarlyExit = true;

                break;
            }
            resultTable.combineTable(result.getClauseResult());
            if (resultTable.isTableEmpty()) {

                isEarlyExit = true;

                break;
            }
        }*/
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
            resultTable.clearResultTable();

            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty()) {

            break;
        }
    }


    set<std::string> retSet = resultTable.getStringSetFromKey(selectedVarName);

    return retSet;
}
