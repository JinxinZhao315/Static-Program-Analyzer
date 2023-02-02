#include <regex>
#include <string>
#include <unordered_set>
#include "Utility.h"

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
};