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
   SelectHandler selectHandler = SelectHandler(pkb);
   std::string selectedVarName = selectHandler.evalSelect(query.getSelectClause(), varTable, resultTable);// update resultTable and return the synonym name

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