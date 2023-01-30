#include <map>
#include "SelectClause.h"
#include "PatternClause.h"
#include "SuchThatClause.h"

class PreProcessedResults {
private:
	std::multimap<std::string, std::string> varTable;
	SelectClause selectClause;
	PatternClause patternClause;
	SuchThatClause suchThatClause;

public:
	PreProcessedResults();
	~PreProcessedResults();
	addVarTable(multimap<std::string, std::string> varTable);
	addSelectClause(SelectClause selectClause);
	addPatternClause(PatternClause patternClause);
	addSuchThatClause(SuchThatClause suchThatClause);
	std::multimap<std::string, std::string> getVarTable();
	SelectClause getSelectClause();
	PatternClause getPatternClause();
	SuchThatClause getSuchThatClause();
};