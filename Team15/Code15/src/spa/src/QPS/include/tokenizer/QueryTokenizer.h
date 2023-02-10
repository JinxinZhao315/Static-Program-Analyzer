#include <map>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include "QPS/include/model/SuchThatClause.h"
#include "QPS/include/model/SelectClause.h"
#include "QPS/include/model/PatternClause.h"
#include "QPS/include/tokenizer/PQLSyntaxChecker.h"
#include "exceptions/PQLSyntaxError.h"
#include "Utility.h"

#pragma once


class QueryTokenizer {
public:
	QueryTokenizer();
	std::pair<std::string, std::string> tokenizeQuery(std::string input);
	void tokenizeClauses(std::string input,
		SelectClause& selectClause,
		SuchThatClause& suchThatClause,
		PatternClause& patternClause);
	std::multimap<std::string, std::string> tokenizeDeclaration(std::string declaration);
	void tokenizeSelectClause(std::string& input, SelectClause& selectClause);
	void tokenizeSuchThatClause(std::string& input, SuchThatClause& suchThatClause);
	void tokenizePatternClause(std::string& input, PatternClause& patternClause);

private:
    PQLSyntaxChecker syntaxChecker;
//	std::string trim(std::string input);
	std::string extractKeyword(std::string &input);
    std::vector<std::string> tokenizeCsv(std::string);
};