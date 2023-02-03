#include <string>
#include <regex>
#include <unordered_set>
#include"exceptions/PQLSyntaxError.h"

#pragma once

//<<<<<<< HEAD
//namespace Utility{
//	std::unordered_set<std::string> designEntitySet = { "procedure", "stmt", "read", "print", 
//		"assign", "call", "while", "if" "variable", "constant" };
//	std::unordered_set<std::string> relationshipSet{ "Follows",
//		"Follows*", "Parent", "Parent*", "Uses", "Modifies" };
//	std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
//	std::string integerFormat = "[1-9][0-9]*";
//	std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
//	std::string underscoredExpr = "_\"[\\s\\S]*\"_";
//	std::string expr = "\"[\\s\\S]*\"";
//	std::string underscore = "_";
//=======

class Utility {
public:
	inline static const std::unordered_set<std::string> designEntitySet = { "procedure", "stmt", "read", "print",
		"assign", "call", "while", "if" "variable", "constant" };
	inline static const std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	inline static const std::string integerFormat = "[1-9][0-9]*";
	inline static const std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	inline static const std::string underscoredExpr = "_\"[\\s\\S]*\"_";
	inline static const std::string expr = "\"[\\s\\S]*\"";
	inline static const std::string underscore = "_";
	//>>>>>>> zhijie-fix-git-error

	inline static const std::string extractKeyword(std::string input) {
		std::size_t nextWhiteSpace = input.find_first_of(" \t\n");
		if (nextWhiteSpace == std::string::npos) {
			throw PQLSyntaxError("PQL syntax error: Invalid keyword");
		}
		std::string keyword = input.substr(0, nextWhiteSpace);
		return keyword;
	};

	//std::string trim(std::string input);

	inline static const std::string getPrimitiveType(std::string input) {
		if (std::regex_match(input, std::regex(synonymFormat))) {
			return "synonym";
		}
		else if (std::regex_match(input, std::regex(integerFormat))) {
			return "integer";
		}
		else if (std::regex_match(input, std::regex(quotedIdentFormat))) {
			return "quotedIdent";
		}
		else if (std::regex_match(input, std::regex(underscoredExpr))) {
			return "underscoredExpr";
		}
		else if (std::regex_match(input, std::regex(expr))) {
			return "expr";
		}
		else if (std::regex_match(input, std::regex(underscore))) {
			return "underscore";
		}
		else {
			return "Invalid";
		}
	};
};