#include <map>
#include <string>
#include <regex>
#include "SuchThatClause.h"
#include "SelectClause.h"
#include "PatternClause.h"
#include "PQLSyntaxChecker.h"

class QueryTokenizer {
public:
	void tokenizeQuery(std::string queryString) {}
private:
	std::string trim(std::string input) {}
	std::multimap<std::string, std::string> tokenizeDeclaration(std::string input) {}
	void tokenizeClauses(std::string input,
		SelectClause& selectClause,
		std::vector<SuchThatClause>& suchThatClauses,
		std::vector<PatternClause>& patternClauses) {}
	void tokenizeSelectClause(std::string& input, SelectClause& selectClause, PQLSyntaxChecker syntaxChecker) {}
	void tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauses, PQLSyntaxChecker syntaxChecker) {}
	void tokenizePatternClause(std::string& input, std::vector<PatternClause>& patternClauses, PQLSyntaxChecker syntaxChecker) {}
	std::string extractKeyword(std::string& input);
	std::string getType(std::string& input);
};