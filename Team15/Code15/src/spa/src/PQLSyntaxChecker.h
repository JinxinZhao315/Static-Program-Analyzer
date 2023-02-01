#include <regex>
#include <string>
#include <unordered_set>
#pragma once

class PQLSyntaxChecker {
public:
	bool validateSynonym(std::string synonym);
	bool PQLSyntaxChecker::validateRelationship(std::string relationship, std::string leftArg, std::string rightArg);
	bool PQLSyntaxChecker::validateStmtRef(std::string input);
	bool PQLSyntaxChecker::validateEntRef(std::string input);
	bool PQLSyntaxChecker::validatePattern(std::string assign, std::string leftArg, std::string rightArg);
	bool PQLSyntaxChecker::validateExprSpec(std::string input);
private:
	std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	std::string integerFormat = "[1-9][0-9]*";
	std::string identFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	std::unordered_set<std::string> relationshipSet{ "Follows",
		"Follows*", "Parent", "Parent*", "Uses", "Modifies" };


};