#include "PQLSyntaxChecker.h"

PQLSyntaxChecker::PQLSyntaxChecker() {}

bool PQLSyntaxChecker::validateSynonym(std::string input) {
	return Utility::getPrimitiveType(input) == "synonym";
}

bool PQLSyntaxChecker::validateRelationship(std::string relationship, std::string leftArg, std::string rightArg) {
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

bool PQLSyntaxChecker::validateDesignEntity(std::string designEntity) {
	if (Utility::designEntitySet.find(designEntity) == Utility::designEntitySet.end()) {
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
	std::string type = Utility::getPrimitiveType(input);
	return type == "expr" || type == "underscoredExpr" || type == "underscore";
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
	std::string type = Utility::getPrimitiveType(input);
	return  type == "synonym" || type == "underscore" || type == "integer";
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
	std::string type = Utility::getPrimitiveType(input);
	return  type == "synonym" || type == "underscore" || type == "quotedIdentFormat";
}

