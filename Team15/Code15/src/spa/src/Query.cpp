#include "Query.h"

Query::Query() {};

Query:: ~Query() {};

void Query::addVarTable(std::multimap<std::string, std::string> varTable) {
	this->varTable = varTable;
}

void Query::addSelectClause(SelectClause selectClause) {
	this->selectClause = selectClause;
}

void Query::addPatternClause(PatternClause patternClause) {
	this->patternClauseVec.push_back(patternClause);
}

void Query::addSuchThatClause(SuchThatClause suchThatClause) {
	this->suchThatClauseVec.push_back(suchThatClause);
}

std::multimap<std::string, std::string> Query::getVarTable() {
	return varTable;
}

SelectClause Query::getSelectClause() {
	return selectClause;
}

std::vector<PatternClause> Query::getPatternClauseVec() {
	return patternClauseVec;
}

std::vector<SuchThatClause> Query::getSuchThatClauseVec() {
	return suchThatClauseVec;
}
