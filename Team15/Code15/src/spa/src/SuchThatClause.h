#include <string>
#include "PQLConstants.h"
#include <vector> 

#pragma once

class SuchThatClause: AbstractClause {
private:
	std::vector <std::string> suchThatVector;
public:
	SuchThatClause(std::string relationship,
		std::string leftType,  std::string leftArg, std::string rightType, std::string rightArg);

	std::string getRelationShip();

	std::pair <std::string, std::string> getLeftPair();

	std::pair <std::string, std::string> getRightPair();

	~SuchThatClause();
};