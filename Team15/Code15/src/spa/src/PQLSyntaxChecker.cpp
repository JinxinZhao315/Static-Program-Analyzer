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
	if (Utility::getPrimitiveType(synonym) != "synonym") {
		return false;
	}
	return validateEntRef(leftArg) && validateExprSpec(rightArg);
}

bool PQLSyntaxChecker::validateExprSpec(std::string input) {
	return Utility::getPrimitiveType(input) == "expr" ||
		Utility::getPrimitiveType(input) == "underscoredExpr" ||
		Utility::getPrimitiveType(input) == "underscore";
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
	return Utility::getPrimitiveType(input) == "synonym" ||
		Utility::getPrimitiveType(input) == "integer" ||
		Utility::getPrimitiveType(input) == "underscore";
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
	return Utility::getPrimitiveType(input) == "synonym" ||
		Utility::getPrimitiveType(input) == "integer" ||
		Utility::getPrimitiveType(input) == "quotedIdent";
}

