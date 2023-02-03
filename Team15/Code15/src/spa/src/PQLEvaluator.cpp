//
// Created by Jinxin Zhao on 2/2/23.
//

#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator() {}

std::string PQLEvaluator::evaluate(Query query) {
   std::unordered_map<std::string, std::vector<std::string>> resultTable;
   std::multimap<std::string, std::string> varTable = query.getVarTable();
   for (auto varPair: varTable) {
       resultTable.insert({varPair.first, std::vector<std::string>()});
   }
   std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
   std::vector<PatternClause> patternVec = query.getPatternClauseVec();

   for (SuchThatClause suchThatCl: suchThatVec) {

   }

   for (PatternClause patternCl: patternVec) {

   }

	return "";
}