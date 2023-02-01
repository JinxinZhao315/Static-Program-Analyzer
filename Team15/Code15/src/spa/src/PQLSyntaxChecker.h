#include <regex>
#include <string>
#include <unordered_set>
#pragma once

class PQLSyntaxChecker {
public:
	bool validateSynonym(std::string synonym);
	bool validateRelationship(std::string relationship, std::string leftArg, std::string rightArg);
    bool validateDesignEntity(std::string designEntity);
	bool validateStmtRef(std::string input);
	bool validateEntRef(std::string input);
	bool validatePattern(std::string assign, std::string leftArg, std::string rightArg);
	bool validateExprSpec(std::string input);
private:
	std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	std::string integerFormat = "[1-9][0-9]*";
	std::string identFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	std::unordered_set<std::string> relationshipSet{ "Follows",
		"Follows*", "Parent", "Parent*", "Uses", "Modifies" };


};