#include <regex>
#include <string>
#include <unordered_set>
#include "Utility.h"
#pragma once

class PQLSyntaxChecker {
public:
	PQLSyntaxChecker();
	bool validateSynonym(std::string synonym);
	bool validateRelationship(std::string relationship, std::string leftArg, std::string rightArg);
    bool validateDesignEntity(std::string designEntity);
	bool validateStmtRef(std::string input);
	bool validateEntRef(std::string input);
    bool validatePattern(std::string synonym, std::string synonymType,
                         std::string firstArg, std::string secondArg, std::string thirdArg);
	bool validateExprSpec(std::string input);
	bool validateAttrRef(std::string input);
	bool validateRef(std::string input);
private:
	std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	std::string integerFormat = "[1-9][0-9]*";
	std::string identFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	std::unordered_set<std::string> relationshipSet{ "Follows",
		"Follows*", "Parent", "Parent*", "Uses", "Modifies" };
};