#include "Query.h"

Query::Query() {};

Query:: ~Query() {};

void Query::addVarTable(std::multimap<std::string, std::string> varTable) {
	varTable = varTable;
}

void Query::addSelectClause(SelectClause selectClause) {
	selectClause = selectClause;
}

void Query::addPatternClause(PatternClause patternClause) {
	patternClause = patternClause;
}

void Query::addSuchThatClause(SuchThatClause suchThatClause) {
	suchThatClause = suchThatClause;
}

std::multimap<std::string, std::string> Query::getVarTable() {
	return varTable;
}

SelectClause Query::getSelectClause() {
	return selectClause;
}

PatternClause Query::getPatternClause() {
	return patternClause; 
}

SuchThatClause Query::getSuchThatClause() {
	return suchThatClause;
}
