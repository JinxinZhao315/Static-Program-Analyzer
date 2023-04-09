#include "qps/include/model/SuchThatClause.h"

SuchThatClause::SuchThatClause() : Clause(SUCH_THAT) {}

SuchThatClause::SuchThatClause(std::string relationship, std::string leftArg, std::string rightArg) : Clause(SUCH_THAT) {
    this->relationship = relationship;
    this->leftArg = leftArg;
    this->rightArg = rightArg;
    ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
    ReferenceType rightType = Utility::getEnumReferenceType(rightArg);
    if (leftType == SYNONYM) {
        addSyn(leftArg);
    }
    if (rightType == SYNONYM) {
        addSyn(rightArg);
    }
}

std::string SuchThatClause::getRelationShip() {
    return this->relationship;
}

std::string SuchThatClause::getLeftArg() {
    return this->leftArg;
}

std::string SuchThatClause::getRightArg() {
    return this->rightArg;
}

SuchThatClause::~SuchThatClause() {}