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
    std::vector<Elem> selectedVarNames = selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternVec = query.getPatternClauseVec();
    std::vector<WithClause> withVec = query.getWithClauseVec();

    bool isEarlyExit = false;

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        ClauseHandler *clauseHandler;
        std::string relationship = suchThatCl.getRelationShip();
        Result result;
        if (relationship == "Follows" || relationship == "Follows*")
        {
            FollowsHandler followsHandler = FollowsHandler(pkb);
            bool isStar = relationship == "Follows" ? false : true;
            result = followsHandler.evaluate(isStar, suchThatCl, resultTable, synonymTable);
        } else if (relationship == "Parent" || relationship == "Parent*") {
            ParentHandler parentHandler = ParentHandler(pkb);
            bool isStar = relationship == "Parent" ? false : true;
            result = parentHandler.evaluate(isStar, suchThatCl, resultTable, synonymTable);
        } else if (relationship == "Modifies") {
            std::string leftArg = suchThatCl.getLeftArg();
            std::string leftType = Utility::getReferenceType(leftArg);

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure") ) {
                ModifiesPHandler modifiesPHandler = ModifiesPHandler(pkb);
                result = modifiesPHandler.evaluate(suchThatCl, resultTable, synonymTable);
            }
            else {
                ModifiesSHandler modifiesSHandler = ModifiesSHandler(pkb);
                result = modifiesSHandler.evaluate(suchThatCl, resultTable, synonymTable);
            }
        } else if (relationship == "Uses") {
            std::string leftArg = suchThatCl.getLeftArg();
            std::string leftType = Utility::getReferenceType(leftArg);

            if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
                UsesPHandler usesPHandler = UsesPHandler(pkb);
                result = usesPHandler.evaluate(suchThatCl, resultTable, synonymTable);
            } else {
                UsesSHandler usesSHandler = UsesSHandler(pkb);
                result = usesSHandler.evaluate(suchThatCl, resultTable, synonymTable);
            }
        } else if (relationship == "Calls" || relationship == "Calls*") {

            CallsHandler callsHandler = CallsHandler(pkb);
            bool isStar = relationship == "Calls" ? false : true;
            result = callsHandler.evaluate(isStar, suchThatCl, resultTable, synonymTable);

        } else if (relationship == "Next" || relationship == "Next*") {

            NextHandler nextHandler = NextHandler(pkb);
            bool isStar = relationship == "Next" ? false : true;
            result = nextHandler.evaluate(isStar, suchThatCl, resultTable, synonymTable);
           
        }
        if (!result.isResultTrue())
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
    for (const PatternClause& patternCl : patternVec)
    {
        if (isEarlyExit) {
            break;
        }
        PatternHandler patternHandler = PatternHandler(pkb);

        Result result = patternHandler.evaluate(patternCl, resultTable, synonymTable);

        if (!result.isResultTrue())
        {
            resultTable.clearResultTable();

            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty()) {

            break;
        }
    }
    for (const WithClause& withCl : withVec) {
        if (isEarlyExit) {
            break;
        }
        WithHandler withHandler = WithHandler(pkb);

        Result result = withHandler.evaluate(withCl, resultTable, synonymTable);
        if (!result.isResultTrue())
        {
            resultTable.clearResultTable();
            break;
        }

        resultTable.combineTable(result.getClauseResult());
        if (resultTable.isTableEmpty()) {
            break;
        }
    }

    set<std::string> retSet = resultTable.getSelectedResult(selectedVarNames, pkb);

    return retSet;
}
