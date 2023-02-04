#include "PQLSyntaxChecker.h"

PQLSyntaxChecker::PQLSyntaxChecker() {}

bool PQLSyntaxChecker::validateSynonym(std::string input) {
	return Utility::getReferenceType(input) == Utility::SYNONYM;
}

bool PQLSyntaxChecker::validateRelationship(std::string relationship, std::string leftArg, std::string rightArg) {
	if (relationship == "Follows" || relationship == "Follows*" || relationship == "Parent" || relationship == "Parent*") {
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
	if (Utility::getReferenceType(synonym) != Utility::SYNONYM) {
		return false;
	}
	return validateEntRef(leftArg) && validateExprSpec(rightArg);
}

bool PQLSyntaxChecker::validateExprSpec(std::string input) {
	return Utility::getReferenceType(input) == Utility::EXPR ||
            Utility::getReferenceType(input) == Utility::UNDERSCORED_EXPR ||
            Utility::getReferenceType(input) == Utility::UNDERSCORE;
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
	return Utility::getReferenceType(input) == Utility::SYNONYM ||
            Utility::getReferenceType(input) == Utility::INTEGER ||
            Utility::getReferenceType(input) == Utility::UNDERSCORE;
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
	return Utility::getReferenceType(input) == Utility::SYNONYM ||
            Utility::getReferenceType(input) == Utility::INTEGER ||
            Utility::getReferenceType(input) == Utility::QUOTED_IDENT;
}

