#include <string>
#include "PQLConstants.h"
#include "AbstractClause.h"
#include <vector>

#pragma once

class PatternClause: AbstractClause {
private:
	std::vector<std::string> patternVector;
public:
	PatternClause(std::string patternType, std::string patternSynonym, std::string leftType,
		std::string leftArg, std::string rightType,std::string rightArg);

	std::pair <std::string, std::string> getPatternPair();

	std::pair <std::string, std::string> getLeftPair();

	std::pair <std::string, std::string> getRightPair();

	~PatternClause();
};