#include <string>
#include <vector>

#pragma once

class PatternClause {
private:
    std::string patternSynonym;
    std::string firstArg;
    std::string secondArg;
    std::string thirdArg;

public:
	PatternClause();

	PatternClause(std::string patternSynonym,
		std::string firstArg, std::string secondArg, std::string thirdArg);

    std::string getPatternSynonym();

	std::string getFirstArg();

	std::string getSecondArg();

    std::string getThirdArg();


	~PatternClause();
};