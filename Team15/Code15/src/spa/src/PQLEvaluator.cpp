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
       if (relationship == "Follows") {
           FollowsHandler followsHandler = FollowsHandler(pkb);
           Result result = followsHandler.evalFollows(suchThatCl, resultTable);
           followsHandler.combineResult(resultTable, result);
       } else if (relationship == "Follows*") {
           FollowsStarHandler followsStarHandler = FollowsStarHandler(pkb);
           Result result = followsStarHandler.evalFollowsStar(suchThatCl, resultTable);
           followsStarHandler.combineResult(resultTable, result);
       }
    }

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



    //   for (PatternClause patternCl: patternVec) {
    //
    //   }


   // TODO: return the values of the selected synonym in ResultTable
   return retStr;
}

