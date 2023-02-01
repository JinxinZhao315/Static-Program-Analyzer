#include <map>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include "SuchThatClause.h"
#include "SelectClause.h"
#include "PatternClause.h"
#include "PQLSyntaxChecker.h"
#include "exceptions/PQLSyntaxError.h"

#pragma once

class QueryTokenizer {
public:
	std::pair<std::string, std::string> tokenizeQuery(std::string input);
	//std::multimap<std::string, std::string> tokenizeDeclaration(std::string input);
	//void tokenizeClauses(std::string input);
	SelectClause tokenizeSelectClause(std::string input, PQLSyntaxChecker syntaxChecker);
	SuchThatClause tokenizeSuchThatClause(std::string input, PQLSyntaxChecker syntaxChecker);
	PatternClause tokenizePatternClause(std::string input, PQLSyntaxChecker syntaxChecker);
	std::string extractKeyword(std::string input);
	std::string getType(std::string& input);
	std::string trim(std::string input);
};