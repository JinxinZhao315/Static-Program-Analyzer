#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() {}

SuchThatClause::SuchThatClause(std::string relationship,
	std::string leftType, std::string leftArg, std::string rightType, std::string rightArg) {
	this->relationship = relationship;
    this->leftType = leftType;
    this->leftArg = leftArg;
    this->rightType = rightType;
    this->rightArg = rightArg;
}

std::string SuchThatClause::getRelationShip() {
	return this->relationship;
}

std::pair <std::string, std::string> SuchThatClause::getLeftPair() {
	return std::pair <std::string, std::string>(this->leftType, this->leftArg);
}

std::pair <std::string, std::string> SuchThatClause::getRightPair() {
	return std::pair <std::string, std::string>(this->rightType, this->rightArg);
}

SuchThatClause::~SuchThatClause() {}