#include "QPS/include/model/Query.h"

Query::Query() {};

Query:: ~Query() {};

void Query::setSynonymTable(std::multimap<std::string, std::string> synonymTable) {
	this->synonymTable = synonymTable;
}

void Query::setSelectClause(SelectClause selectClause) {
	this->selectClause = selectClause;
}

void Query::setPatternClauseVec(std::vector<PatternClause> patternClauseVec) {
	this->patternClauseVec = patternClauseVec;
}

void Query::setSuchThatClauseVec(std::vector<SuchThatClause> suchThatClauseVec) {
	this->suchThatClauseVec = suchThatClauseVec;
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
