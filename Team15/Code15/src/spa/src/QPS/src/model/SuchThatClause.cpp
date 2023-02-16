#include "QPS/include/model/SuchThatClause.h"

SuchThatClause::SuchThatClause() {}

SuchThatClause::SuchThatClause(std::string relationship, std::string leftArg, std::string rightArg) {
    this->relationship = relationship;
    this->leftArg = leftArg;
    this->rightArg = rightArg;
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