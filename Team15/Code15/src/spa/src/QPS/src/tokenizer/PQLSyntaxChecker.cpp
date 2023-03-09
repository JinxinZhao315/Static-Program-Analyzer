#include "QPS/include/tokenizer/PQLSyntaxChecker.h"

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
    else if (relationship == "Calls" || relationship == "Calls*") {
        return validateEntRef(leftArg) && validateEntRef(rightArg);
    }
    else if (relationship == "Next" || relationship == "Next*" ||
        relationship == "Affects" || relationship == "Affects*") {
        return validateStmtRef(leftArg) && validateStmtRef(rightArg);
    }
	else {
		return false;
	}
}

bool PQLSyntaxChecker::validateDesignEntity(std::string designEntity) {
	if (Utility::designEntitySet.find(designEntity) == Utility::designEntitySet.end()) {
        return false;
    }
    return true;
}

bool PQLSyntaxChecker::validatePattern(std::string synonym, std::string synonymType, std::string firstArg,
                                       std::string secondArg, std::string thirdArg) {
    if (Utility::getReferenceType(synonym) != Utility::SYNONYM) {
        return false;
    }
    if (synonymType == "assign") {
        return validateEntRef(firstArg) && validateExprSpec(secondArg);
    } else if (synonymType == "while") {
        return validateEntRef(firstArg) && secondArg == Utility::UNDERSCORE;
    } else { // if (synonymType == "if")
        return validateEntRef(firstArg) && secondArg == Utility::UNDERSCORE && thirdArg == Utility::UNDERSCORE;
    }
}


bool PQLSyntaxChecker::validateExprSpec(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::EXPR ||
            type == Utility::QUOTED_IDENT || // Because when expr only has 1 variable name e.g. x1, it also matches quoted ident
            type == Utility::UNDERSCORED_EXPR ||
            type == Utility::UNDERSCORE;
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::SYNONYM ||
            type == Utility::INTEGER ||
            type == Utility::UNDERSCORE;
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::SYNONYM ||
            type== Utility::UNDERSCORE ||
            type == Utility::QUOTED_IDENT;
}

