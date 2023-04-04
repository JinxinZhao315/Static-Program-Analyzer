#include "QPS/include/tokenizer/PQLSyntaxChecker.h"

PQLSyntaxChecker::PQLSyntaxChecker() {}

bool PQLSyntaxChecker::validateSynonym(std::string input) {
	return Utility::getReferenceType(input) == Utility::synonym;
}

bool PQLSyntaxChecker::validateRelationship(std::string relationship, std::string leftArg, std::string rightArg) {
    Relationship enumRelationship = Utility::getRelationshipFromString(relationship);
    ReferenceType enumLeftRefType = Utility::getEnumReferenceType(leftArg);
    ReferenceType enumRightRefType = Utility::getEnumReferenceType(rightArg);
	if (enumRelationship == FOLLOWS || enumRelationship == FOLLOWS_STAR || enumRelationship == PARENT || enumRelationship == PARENT_STAR) {
		return validateStmtRef(enumLeftRefType) && validateStmtRef(enumRightRefType);
	}
	else if (enumRelationship == USES || enumRelationship == MODIFIES) {
		return (validateStmtRef(enumLeftRefType) || validateEntRef(enumLeftRefType)) && validateEntRef(enumRightRefType);
    }
    else if (enumRelationship == CALLS || enumRelationship == CALLS_STAR) {
        return validateEntRef(enumLeftRefType) && validateEntRef(enumRightRefType);
    }
    else if (enumRelationship == NEXT || enumRelationship == NEXT_STAR ||
        enumRelationship == AFFECTS || enumRelationship == AFFECTS_STAR) {
        return validateStmtRef(enumLeftRefType) && validateStmtRef(enumRightRefType);
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
    ReferenceType enumReferenceType = Utility::getEnumReferenceType(synonym);
    if (enumReferenceType != SYNONYM) {
        return false;
    }
    DesignEntity enumDesignEntity = Utility::getDesignEntityFromString(synonymType);
    ReferenceType firstType = Utility::getEnumReferenceType(firstArg);
    ReferenceType secondType = Utility::getEnumReferenceType(secondArg);

    if (enumDesignEntity == ASSIGN_ENTITY) {
        return validateEntRef(firstType) && validateExprSpec(secondType);
    } else if (enumDesignEntity == WHILE_ENTITY) {
        return validateEntRef(firstType) && secondArg == Utility::underscore;
    } else {
        return validateEntRef(firstType) && secondArg == Utility::underscore && thirdArg == Utility::underscore;
    }
}


bool PQLSyntaxChecker::validateExprSpec(ReferenceType type) {
	return type == EXPR ||
            type == QUOTED_IDENT || // Because when expr only has 1 variable name e.g. x1, it also matches quoted ident
            type == UNDERSCORED_EXPR ||
            type == UNDERSCORE;
}

bool PQLSyntaxChecker::validateStmtRef(ReferenceType type) {
	return type == SYNONYM ||
            type == INTEGER ||
            type == UNDERSCORE;
}

bool PQLSyntaxChecker::validateEntRef(ReferenceType type) {
	return type == SYNONYM ||
            type== UNDERSCORE ||
            type == QUOTED_IDENT;
}

bool PQLSyntaxChecker::validateAttrRef(std::string input) {
        std::size_t periodIndex = input.find_first_of(Utility::ending);
        std::string synName = input.substr(0, periodIndex);
        std::string attrName = input.substr(periodIndex + 1);
        //synonym is valid, attrName is valid
        return validateSynonym(synName) && (Utility::attrNameSet.find(attrName) != Utility::attrNameSet.end());
}
