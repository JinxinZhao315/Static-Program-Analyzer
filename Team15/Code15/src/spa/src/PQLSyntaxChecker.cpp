#include "PQLSyntaxChecker.h"

bool PQLSyntaxChecker::validateSynonym(std::string synonym) {
	return std::regex_match(synonym, std::regex(synonymFormat));
}

bool PQLSyntaxChecker::validateRelationship(std::string relationship, std::string leftArg, std::string rightArg) {
	/*if (PQLSyntaxChecker::relationshipSet.find(relationship) != PQLSyntaxChecker::relationshipSet.end()) {
		return false;
	}*/
	if (relationship == "Follows" || relationship == "Follows*" || relationship == "Parent" || relationship == "parent*") {
		return validateStmtRef(leftArg) && validateStmtRef(rightArg);
	}
	else if (relationship == "Uses" || relationship == "Modifies") {
		return (validateStmtRef(leftArg) || validateEntRef(leftArg)) && validateEntRef(rightArg);
	}
	else {
		return false;
	}
}

bool validateDesignEntity(std::string designEntity) {
    std::unordered_set<std::string> designEntitySet = { "Uses", "Modifies", "Parent",  "Parent*", "Follows", "Follows*" };
    if (designEntitySet.find(designEntity) == designEntitySet.end()) {
        return false;
    }
}


bool PQLSyntaxChecker::validatePattern(std::string synonym, std::string leftArg, std::string rightArg) {
	/*if (PQLSyntaxChecker::relationshipSet.find(relationship) != PQLSyntaxChecker::relationshipSet.end()) {
		return false;
	}*/
	if (validateSynonym(synonym) == false) {
		return false;
	}
	return validateEntRef(leftArg) && validateExprSpec(rightArg);
}

bool PQLSyntaxChecker::validateExprSpec(std::string input) {
	return std::regex_match(input, std::regex("\"[\\s\\S]*\""));
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
	return std::regex_match(input, std::regex(synonymFormat)) ||
		std::regex_match(input, std::regex(integerFormat)) ||
		std::regex_match(input, std::regex("_"));
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
	return std::regex_match(input, std::regex(synonymFormat)) ||
		std::regex_match(input, std::regex(integerFormat)) ||
		std::regex_match(input, std::regex(identFormat));
}

