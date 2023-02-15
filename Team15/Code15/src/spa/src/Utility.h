#include<string>
#include<regex>
#include<unordered_set>
#include <algorithm>
#include <iterator>
#include <set>
#include"exceptions/PQLSyntaxError.h"

#pragma once

class Utility {
public:
	inline static const std::unordered_set<std::string> designEntitySet = { "procedure", "stmt", "read", "print",
		"assign", "call", "while", "if", "variable", "constant" };
	inline static const std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	inline static const std::string integerFormat = "[1-9][0-9]*";
	inline static const std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	inline static const std::string underscoredExpr = "_\"[\\s\\S]*\"_";
	inline static const std::string expr = "\"[\\s\\S]*\"";

    inline static const std::string WHITESPACES = " \t\n";
    inline static const std::string QUOTE = "\"";
	inline static const std::string UNDERSCORE = "_";
    inline static const std::string EXPR = "expr";
    inline static const std::string UNDERSCORED_EXPR = "underscoredExpr";
    inline static const std::string QUOTED_IDENT = "quotedIdent";
    inline static const std::string INTEGER = "integer";
    inline static const std::string SYNONYM = "synonym";
    inline static const std::string INVALID = "Invalid";


    inline static const std::string extractKeyword(std::string input) {
		std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
		if (nextWhiteSpace == std::string::npos) {
			throw PQLSyntaxError("PQL syntax error: Invalid keyword");
		}
		std::string keyword = input.substr(0, nextWhiteSpace);
		return keyword;
	};

	inline static const std::string getReferenceType(std::string input) {
		if (std::regex_match(input, std::regex(synonymFormat))) {
			return SYNONYM;
		}
		else if (std::regex_match(input, std::regex(integerFormat))) {
			return INTEGER;
		}
		else if (std::regex_match(input, std::regex(quotedIdentFormat))) {
			return QUOTED_IDENT;
		}
		else if (std::regex_match(input, std::regex(underscoredExpr))) {
			return UNDERSCORED_EXPR;
		}
		else if (std::regex_match(input, std::regex(expr))) {
			return EXPR;
		}
		else if (std::regex_match(input, std::regex(UNDERSCORE))) {
			return UNDERSCORE;
		}
		else {
			return INVALID;
		}
	};

    inline static const std::string trim(std::string input, std::string exprToTrim) {
        std::string trimmed = input;
        std::size_t firstWhitespace = trimmed.find_first_not_of(exprToTrim);
        // trim left
        if (firstWhitespace != std::string::npos) {
            trimmed = trimmed.substr(firstWhitespace);
        }
        // trim right
        std::size_t lastWhitespace = trimmed.find_last_not_of(exprToTrim);
        if (lastWhitespace != std::string::npos) {
            trimmed = trimmed.substr(0, lastWhitespace + 1);
        }
        return trimmed;
    };

	inline static const std::set<std::string> getSetIntersection(std::set<std::string> firstSet, std::set<std::string> secondSet) {
		std::set<std::string> resultSet;
		std::set_intersection(firstSet.begin(), firstSet.end(),
			secondSet.begin(), secondSet.end(),
			std::inserter(resultSet, resultSet.begin()));
		return resultSet;
	}
};


