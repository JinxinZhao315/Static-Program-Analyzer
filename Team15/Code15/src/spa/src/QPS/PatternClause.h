#include <string>
#include <vector>

#pragma once

class PatternClause {
private:
    std::string patternSynonym;
    std::string leftArg;
    std::string rightArg;
public:
	PatternClause();

	PatternClause(std::string patternSynonym,
		std::string leftArg, std::string rightArg);

    std::string getPatternSynonym();

	std::string getLeftArg();

	std::string getRightArg();

	~PatternClause();
};