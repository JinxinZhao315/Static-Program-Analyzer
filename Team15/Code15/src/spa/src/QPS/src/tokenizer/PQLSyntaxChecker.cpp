#include "QPS/include/tokenizer/PQLSyntaxChecker.h"

PQLSyntaxChecker::PQLSyntaxChecker() {}

bool PQLSyntaxChecker::validateSynonym(std::string input) {
	return Utility::getReferenceType(input) == Utility::synonym;
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
    if (Utility::getReferenceType(synonym) != Utility::synonym) {
        return false;
    }
    if (synonymType == "assign") {
        return validateEntRef(firstArg) && validateExprSpec(secondArg);
    } else if (synonymType == "while") {
        return validateEntRef(firstArg) && secondArg == Utility::underscore;
    } else { // if (synonymType == "if")
        return validateEntRef(firstArg) && secondArg == Utility::underscore && thirdArg == Utility::underscore;
    }
}


bool PQLSyntaxChecker::validateExprSpec(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::expr ||
            type == Utility::quoted_ident || // Because when expr only has 1 variable name e.g. x1, it also matches quoted ident
            type == Utility::underscored_expr ||
            type == Utility::underscore;
}

bool PQLSyntaxChecker::validateStmtRef(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::synonym ||
            type == Utility::integer ||
            type == Utility::underscore;
}

bool PQLSyntaxChecker::validateEntRef(std::string input) {
    std::string type = Utility::getReferenceType(input);
	return type == Utility::synonym ||
            type== Utility::underscore ||
            type == Utility::quoted_ident;
}

bool PQLSyntaxChecker::validateAttrRef(std::string input) {
        std::size_t periodIndex = input.find_first_of(".");
        std::string synName = input.substr(0, periodIndex);
        std::string attrName = input.substr(periodIndex + 1);
        //synonym is valid, attrName is valid
        return validateSynonym(synName) && (Utility::attrNameSet.find(attrName) != Utility::attrNameSet.end());
}


bool PQLSyntaxChecker::validateRef(std::string input) {
    std::string type = Utility::getReferenceType(input);
    return type == Utility::quoted_ident ||
        type == Utility::integer ||
        validateAttrRef(input);
}