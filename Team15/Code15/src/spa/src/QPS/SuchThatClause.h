#include <string>
#include <vector> 

#pragma once

class SuchThatClause {
private:
    std::string relationship;
    std::string leftArg;
    std::string rightArg;
public:
	SuchThatClause();

	SuchThatClause(std::string relationship, std::string leftArg, std::string rightArg);

	std::string getRelationShip();

	std::string getLeftArg();

	std::string getRightArg();

	~SuchThatClause();
};