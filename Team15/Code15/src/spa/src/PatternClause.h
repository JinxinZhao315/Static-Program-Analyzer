#include <string>
#include <vector>

#pragma once

class PatternClause {
private:
	//std::vector<std::string> patternVector;
    std::string patternType;
    std::string patternSynonym;
    std::string leftType;
    std::string leftArg;
    std::string rightType;
    std::string rightArg;
public:
	PatternClause();

	PatternClause(std::string patternType, std::string patternSynonym, std::string leftType,
		std::string leftArg, std::string rightType,std::string rightArg);

	std::pair <std::string, std::string> getPatternPair();

	std::pair <std::string, std::string> getLeftPair();

	std::pair <std::string, std::string> getRightPair();

	~PatternClause();
};