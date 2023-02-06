#include <map>
#include "SelectClause.h"
#include "PatternClause.h"
#include "SuchThatClause.h"
#pragma once

class Query
{

private:
	std::multimap<std::string, std::string> varTable;
    SelectClause selectClause;
    std::vector<PatternClause> patternClauseVec;
	std::vector<SuchThatClause> suchThatClauseVec;
//	PatternClause patternClause;
//	SuchThatClause suchThatClause;

public:
	Query();
	~Query();
	void addVarTable(std::multimap<std::string, std::string> varTable);
	void addSelectClause(SelectClause selectClause);
	void addPatternClause(PatternClause patternClause);
	void addSuchThatClause(SuchThatClause suchThatClause);
	std::multimap<std::string, std::string> getVarTable();
	SelectClause getSelectClause();
    //PatternClause getPatternClause();
    //SuchThatClause getSuchThatClause();
    std::vector<PatternClause> getPatternClauseVec();
    std::vector<SuchThatClause> getSuchThatClauseVec();
};