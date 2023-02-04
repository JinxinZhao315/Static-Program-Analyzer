//
// Created by Jinxin Zhao on 2/2/23.
//

#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB pkb) {
    this->pkb = pkb;
}

std::string PQLEvaluator::evaluate(Query query) {
    ResultTable resultTable = ResultTable();

   std::multimap<std::string, std::string> varTable = query.getVarTable();

   // resultTable.insert({varName, std::set<std::string>()});
   SelectClause selectClause = query.getSelectClause();
   std::vector<string> returnSynons = parseSelectClause(selectClause);

   std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
   std::vector<PatternClause> patternVec = query.getPatternClauseVec();

   for (SuchThatClause suchThatCl: suchThatVec) {
       std::string relationship = suchThatCl.getRelationShip();
       if (relationship == "Follows" || relationship == "Follows*") {
           FollowsHandler followsHandler = FollowsHandler(pkb, resultTable);
           //evalFollows return true/false
           Result result = followsHandler.evalFollows(suchThatCl);
       }
   }

   for (PatternClause patternCl: patternVec) {

   }

   // TODO: return the values of the selected synonym in ResultTable
	return "";
}

// TODO: finish this function
std::vector<string> PQLEvaluator::parseSelectClause(SelectClause selectClause) {
    std::vector<string> returnVars;
    // Put every variable name selected in selectClause into ResultTable keys,
    // and add full set of possible values of that variable into ResultTable values.
    // return vector of return variables
    return returnVars;
}