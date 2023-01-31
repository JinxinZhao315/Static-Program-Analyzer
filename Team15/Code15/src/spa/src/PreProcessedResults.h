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
	void addVarTable(std::multimap<std::string, std::string> varTable);
	void addSelectClause(SelectClause selectClause);
	void addPatternClause(PatternClause patternClause);
	void addSuchThatClause(SuchThatClause suchThatClause);
	std::multimap<std::string, std::string> getVarTable();
	SelectClause getSelectClause();
	PatternClause getPatternClause();
	SuchThatClause getSuchThatClause();
};