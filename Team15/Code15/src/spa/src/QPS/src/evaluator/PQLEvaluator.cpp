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

    for (Elem e : selectedElems) {
        selectedElemName.push_back(e.getSynName());
    }

    for (SuchThatClause suchThatCl : suchThatVec){
        clauseArgVec.push_back(suchThatCl.getLeftArg());
        clauseArgVec.push_back(suchThatCl.getRightArg());
    }

    for (PatternClause& patternCl : patternVec) {
        clauseArgVec.push_back(patternCl.getPatternSynonym());
        clauseArgVec.push_back(patternCl.getFirstArg());
        clauseArgVec.push_back(patternCl.getSecondArg());
        clauseArgVec.push_back(patternCl.getThirdArg());
    }

    for (WithClause& withCl : withVec) {
        clauseArgVec.push_back(withCl.getFirstArgStr());
        clauseArgVec.push_back(withCl.getSecondArgStr());
    }

    //selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    for (SuchThatClause suchThatCl : suchThatVec)
    {
        std::string relationship = suchThatCl.getRelationShip();

        Result result = getSuchThatResult(suchThatCl, relationship, resultTable, synonymTable);

        if (!result.isResultTrue())
        {

            resultTable.clearResultTable();

            isEarlyExit = true;

            break;
        }
        resultTable.combineTable(result.getClauseResult());
        //there used to be some syns in the table but now it is empty
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {

            isEarlyExit = true;

            break;
        }
        //no such arg left in the following clause, can delete it in resultTable
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(suchThatCl.getLeftArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(suchThatCl.getRightArg());
        }
        clauseArgVecIndex++;
    }

    for (PatternClause& patternCl : patternVec)
    {
        if (isEarlyExit) {
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
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            isEarlyExit = true;
            break;
        }

        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(patternCl.getPatternSynonym());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(patternCl.getFirstArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(patternCl.getSecondArg());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(patternCl.getThirdArg());
        }
        clauseArgVecIndex++;
    }

    for (WithClause& withCl : withVec) {
        if (isEarlyExit) {
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
        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            isEarlyExit = true;
            break;
        }

        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(withCl.getFirstArgStr());
        }
        clauseArgVecIndex++;
        if (!isArgUsedLater(selectedElemName, clauseArgVec, clauseArgVecIndex)) {
            resultTable.deleteSynonym(withCl.getSecondArgStr());
        }
        clauseArgVecIndex++;
    }

    selectHandler.evalSelect(query.getSelectClause(), synonymTable, resultTable); // update resultTable and return the synonym name

    set<std::string> retSet = resultTable.getSelectedResult(selectedElems, pkb, isEarlyExit);

    return retSet;
}

Result PQLEvaluator::getSuchThatResult(SuchThatClause suchThatCl, const string& relationship, ResultTable resultTable, std::multimap<std::string, std::string> synonymTable) {
    Result result;
    bool isStar;

    if (relationship == "Follows" || relationship == "Follows*"
    || relationship == "Parent" || relationship == "Parent*"
    || relationship == "Next" || relationship == "Next*"
    || relationship == "Calls" || relationship == "Calls*")
    {
        SuchThatHandler suchThatHandler = SuchThatHandler(pkb);
        result = suchThatHandler.evaluate(relationship, suchThatCl, synonymTable);

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

    } else {
        throw PQLSyntaxError("PQL Syntax error: invalid relationship");
    }

    return result;
}

bool PQLEvaluator::isArgUsedLater(std::vector<std::string> selectedSyn, std::vector<std::string> argList, int currArgPos) {
    std::string argName = argList[currArgPos];
    auto argNextOccur = std::find(argList.begin() + currArgPos + 1, argList.end(), argName);
    bool isArgSelected = std::find(selectedSyn.begin(), selectedSyn.end(), argName) != selectedSyn.end();
    if (argNextOccur == argList.end() && !isArgSelected) {
        return false;
    }
    else {
        return true;
    }
}