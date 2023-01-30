#include "PreProcessedResults.h"

PreProcessedResults::PreProcessedResults() {};

PreProcessedResults:: ~PreProcessedResults() {};

PreProcessedResults::addVarTable(multimap<std::string, std::string> varTable) {
	varTable = varTable;
}

PreProcessedResults::addSelectClause(SelectClause selectClause) {
	selectClause = selectClause;
}

PreProcessedResults::addPatternClause(PatternClause patternClause) {
	patternClause = patternClause;
}

PreProcessedResults::addSuchThatClause(SuchThatClause suchThatClause) {
	suchThatClause = suchThatClause;
}

std::multimap<std::string, std::string> PreProcessedResults::getVarTable() {
	return varTable;
}

SelectClause PreProcessedResults::getSelectClause() {
	return selectClause;
}

PatternClause PreProcessedResults::getPatternClause() {
	return patternClause; 
}

SuchThatClause PreProcessedResults::getSuchThatClause() {
	return suchThatClause;
}
