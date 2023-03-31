#include "QPS/include/model/SuchThatClause.h"

SuchThatClause::SuchThatClause() : Clause(SUCH_THAT) {}

SuchThatClause::SuchThatClause(std::string relationship, std::string leftArg, std::string rightArg) : Clause(SUCH_THAT) {
    this->relationship = relationship;
    this->leftArg = leftArg;
    this->rightArg = rightArg;
    std::string leftType = Utility::getReferenceType
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