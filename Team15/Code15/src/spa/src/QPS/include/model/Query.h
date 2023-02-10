#include <map>
#include "QPS/include/model/PatternClause.h"
#include "SynonymTable.h"
#include "SelectClause.h"

#include "SuchThatClause.h"
#pragma once

class Query
{

private:
    //Todo: SynonymTable synonymTable;
	std::multimap<std::string, std::string> synonymTable;
    SelectClause selectClause;
    std::vector<PatternClause> patternClauseVec;
	std::vector<SuchThatClause> suchThatClauseVec;

public:
	Query();
	~Query();
	void addSynonymTable(std::multimap<std::string, std::string> synonymTable);
	void addSelectClause(SelectClause selectClause);
	void addPatternClause(PatternClause patternClause);
	void addSuchThatClause(SuchThatClause suchThatClause);
	std::multimap<std::string, std::string> getSynonymTable();
	SelectClause getSelectClause();
    std::vector<PatternClause> getPatternClauseVec();
    std::vector<SuchThatClause> getSuchThatClauseVec();
};