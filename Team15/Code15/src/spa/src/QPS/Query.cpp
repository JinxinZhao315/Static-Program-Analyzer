#include "Query.h"

Query::Query() {};

Query:: ~Query() {};

void Query::addSynonymTable(std::multimap<std::string, std::string> varTable) {
	this->synonymTable = varTable;
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

std::multimap<std::string, std::string> Query::getSynonymTable() {
	return synonymTable;
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
