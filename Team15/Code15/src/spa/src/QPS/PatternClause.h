#include <string>
#include <vector>

#pragma once

class PatternClause {
private:
    //std::vector<std::string> patternVector;
    std::string patternType;
    std::string patternSynonym;
    std::string leftArg;
    std::string rightArg;
public:
	PatternClause();

	PatternClause(std::string patternType, std::string patternSynonym,
		std::string leftArg, std::string rightArg);

    std::string getPatternType();

    std::string getPatternSynonym();

	std::string getLeftArg();

	std::string getRightArg();

	~PatternClause();
};