#include <map>
#include <memory>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "QPS/include/model/SuchThatClause.h"
#include "QPS/include/model/SelectClause.h"
#include "QPS/include/model/PatternClause.h"
#include "QPS/include/model/WithClause.h"
#include "QPS/include/tokenizer/PQLSyntaxChecker.h"
#include "exceptions/PQLSemanticError.h"
#include "exceptions/PQLSyntaxError.h"
#include "Utility.h"

#pragma once


class QueryTokenizer {
public:
	QueryTokenizer();
	std::pair<std::string, std::string> tokenizeQuery(std::string input);
	void tokenizeClauses(std::string input,
        std::multimap<std::string, std::string> varTable,
		SelectClause& selectClause,
		std::vector<SuchThatClause>& suchThatClauseVec,
		std::vector<PatternClause>& patternClauseVec,
		std::vector<WithClause>& withClauseVec);
	std::multimap<std::string, std::string> tokenizeDeclaration(std::string declaration);
	void tokenizeSelectClause(std::string& input, std::multimap<std::string, std::string> varTable, SelectClause& selectClause);
	void tokenizeSuchThatClause(std::string& input, std::vector<SuchThatClause>& suchThatClauseVec);
	void tokenizePatternClause(std::string& input, std::multimap<std::string, std::string> varTable, std::vector<PatternClause>& patternClauseVec);
	void tokenizeWithClause(std::string& input, std::vector<WithClause>& withClauseVec, std::multimap<std::string, std::string> varTable);
private:
    PQLSyntaxChecker syntaxChecker;
//	std::string trim(std::string input);
	std::string extractKeyword(std::string &input);
    std::vector<std::string> tokenizeCsv(std::string);
	Ref tokenizeRef(std::string input, std::multimap<std::string, std::string> varTable);
};