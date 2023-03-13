#include <map>
#include "QPS/include/model/PatternClause.h"
#include "SynonymTable.h"
#include "SelectClause.h"
#include "WithClause.h"

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
	std::vector<WithClause> withClauseVec;
public:
	Query();
	~Query();
	void setSynonymTable(std::multimap<std::string, std::string> synonymTable);
	void setSelectClause(SelectClause selectClause);
	void setPatternClauseVec(std::vector<PatternClause> patternClauseVec);
	void setSuchThatClauseVec(std::vector<SuchThatClause> suchThatClauseVec);
	void setWithClauseVec(std::vector<WithClause> withClauseVec);
	std::multimap<std::string, std::string> getSynonymTable();
	SelectClause getSelectClause();
    std::vector<PatternClause> getPatternClauseVec();
    std::vector<SuchThatClause> getSuchThatClauseVec();
	std::vector<WithClause> getWithClauseVec();
};