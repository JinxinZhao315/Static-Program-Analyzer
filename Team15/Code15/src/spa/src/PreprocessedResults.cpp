#include "PreProcessedResults.h"

PreProcessedResults::PreProcessedResults() {};

PreProcessedResults:: ~PreProcessedResults() {};

void PreProcessedResults::addVarTable(std::multimap<std::string, std::string> varTable) {
	varTable = varTable;
}

void PreProcessedResults::addSelectClause(SelectClause selectClause) {
	selectClause = selectClause;
}

void PreProcessedResults::addPatternClause(PatternClause patternClause) {
	patternClause = patternClause;
}

void PreProcessedResults::addSuchThatClause(SuchThatClause suchThatClause) {
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
