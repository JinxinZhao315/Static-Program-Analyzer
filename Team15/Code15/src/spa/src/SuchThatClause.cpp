#include "SuchThatClause.h"

SuchThatClause::SuchThatClause() {}

SuchThatClause::SuchThatClause(std::string relationship,
	std::string leftType, std::string leftArg, std::string rightType, std::string rightArg) {
	suchThatVector.push_back(relationship);
	suchThatVector.push_back(leftType);
	suchThatVector.push_back(leftArg);
	suchThatVector.push_back(rightType);
	suchThatVector.push_back(rightArg);
}

std::string SuchThatClause::getRelationShip() {
	return suchThatVector[0];
}

std::pair <std::string, std::string> SuchThatClause::getLeftPair() {
	return std::pair <std::string, std::string>(suchThatVector[1], suchThatVector[2]);
}

std::pair <std::string, std::string> SuchThatClause::getRightPair() {
	return std::pair <std::string, std::string>(suchThatVector[3], suchThatVector[4]);
}

SuchThatClause::~SuchThatClause() {}