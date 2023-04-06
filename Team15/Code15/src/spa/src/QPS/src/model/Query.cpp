#include "QPS/include/model/Query.h"

Query::Query() {};

Query:: ~Query() {};

void Query::setSynonymTable(std::multimap<std::string, std::string> synonymTable) {
	this->synonymTable = synonymTable;
}

void Query::setClauseList(std::vector<Clause*> evalClauses) {
	this->clauseList = evalClauses;
}

void Query::addSelectClause(SelectClause* selectClause) {
	clauseList.push_back(selectClause);
}
void Query::addAllSuchThatClauses(std::vector<SuchThatClause*>& suchThatClauseVec) {
	for (SuchThatClause* suchThatClause: suchThatClauseVec) {
		clauseList.push_back(suchThatClause);
	}
}
void Query::addAllPatternClauses(std::vector<PatternClause*>& patternClauseVec) {
	for (PatternClause* patternClause : patternClauseVec) {
		clauseList.push_back(patternClause);
	}
}
void Query::addAllWithClauses(std::vector<WithClause*>& withClauseVec) {
	for (WithClause* withClause : withClauseVec) {
		clauseList.push_back(withClause);
	}
}

std::multimap<std::string, std::string> Query::getSynonymTable() {
	return synonymTable;
}

std::vector<Clause*> Query::getClauseList() {
	return clauseList;
}

SelectClause* Query::getSelectClause() {
	return (static_cast<SelectClause*>(clauseList.back()));
}