#include <regex>
#include <string>
#include <unordered_set>
#include "common/include/utils/Utility.h"
#pragma once

class PQLSyntaxChecker {
public:
	PQLSyntaxChecker();
	bool validateSynonym(std::string synonym);
	bool validateRelationship(std::string relationship, std::string leftArg, std::string rightArg);
    bool validateDesignEntity(std::string designEntity);
	bool validateStmtRef(ReferenceType type);
	bool validateEntRef(ReferenceType type);
    bool validatePattern(std::string synonym, std::string synonymType,
                         std::string firstArg, std::string secondArg, std::string thirdArg);
	bool validateExprSpec(ReferenceType type);
	bool validateAttrRef(std::string input);
	bool validateRef(std::string input);
};