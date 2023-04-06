#include <map>
#include "PatternClause.h"
#include "SelectClause.h"
#include "WithClause.h"
#include "SuchThatClause.h"
#include "ClauseEvalGroup.h"
#pragma once

class Query
{

private:
	std::multimap<std::string, std::string> synonymTable;
	std::vector<Clause*> clauseList;
public:
	Query();
	~Query();
	void setSynonymTable(std::multimap<std::string, std::string> synonymTable);
	void setClauseList(std::vector<Clause*> evalClauses);
	void addSelectClause(SelectClause* selectClase);
	void addAllSuchThatClauses(std::vector<SuchThatClause*>& suchThatClauseVec);
	void addAllPatternClauses(std::vector<PatternClause*>& patternClauseVec);
	void addAllWithClauses(std::vector<WithClause*>& withClauseVec);
	std::multimap<std::string, std::string> getSynonymTable();
	std::vector<Clause*> getClauseList();
	SelectClause* getSelectClause();
};