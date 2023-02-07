#include<string>
#include<regex>
#include<unordered_set>
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
};
