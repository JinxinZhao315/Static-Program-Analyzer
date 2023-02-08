//
// Created by Jinxin Zhao on 2/2/23.
//

#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB& pkb) {
    this->pkb = pkb;
}

std::string PQLEvaluator::evaluate(Query query) {
    ResultTable resultTable = ResultTable();

    std::multimap<std::string, std::string> varTable = query.getVarTable();
    SelectHandler selectHandler = SelectHandler(pkb);
    std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);// update resultTable and return the synonym name

    std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternVec = query.getPatternClauseVec();

    for (SuchThatClause suchThatCl: suchThatVec) {
       std::string relationship = suchThatCl.getRelationShip();
       if (relationship == "Follows" || relationship == "Follows*") {
           FollowsHandler followsHandler = FollowsHandler(pkb);
           bool isStar = relationship == "Follows" ? false : true;
           Result result = followsHandler.evalFollowsStar(isStar, suchThatCl, resultTable, varTable);
           if (result.isResultTrue() == false) {
               resultTable.deleteKeyValuePair(selectedVarName);
               resultTable.insertKeyValuePair(selectedVarName, {});
               break;
           }
           followsHandler.combineResult(resultTable, result);
       } 
       if (relationship == "Parent" || relationship == "Parent*") {
           ParentHandler parentHandler = ParentHandler(pkb);
           bool isStar = relationship == "Parent" ? false : true;
           Result result = parentHandler.evalParentStar(isStar, suchThatCl, resultTable, varTable);
           if (result.isResultTrue() == false) {
               resultTable.deleteKeyValuePair(selectedVarName);
               resultTable.insertKeyValuePair(selectedVarName, {});
               break;
           }
           parentHandler.combineResult(resultTable, result);
       }
       if (relationship == "Modifies") {
           ModifiesHandler modifiesHandler = ModifiesHandler(pkb);
         
           Result result = modifiesHandler.evalModifies(suchThatCl, resultTable, varTable);
           if (result.isResultTrue() == false) {
               resultTable.deleteKeyValuePair(selectedVarName);
               resultTable.insertKeyValuePair(selectedVarName, {});
               break;
           }
           modifiesHandler.combineResult(resultTable, result);
       }


    }

       for (PatternClause patternCl: patternVec) {

       }

    // return the values of the selected synonym in ResultTable
    std::string retStr;
    set<string> retSet = resultTable.getValueFromKey(selectedVarName);
    if (retSet.empty()) {
        retStr = "None";
    } else {
        retStr = std::accumulate(begin(retSet),
                                 end(retSet),
                                 string{},
                                 [](const string& a, const string &b ) {
                                     return a.empty() ? b: a + ',' + b; } );
    }


   return retStr;
}

