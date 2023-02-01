#include "PatternClause.h"

PatternClause::PatternClause() {}

PatternClause::PatternClause(std::string patternType, std::string patternSynonym, std::string leftType,
	std::string leftArg, std::string rightType, std::string rightArg) {
	patternVector.push_back(patternType);
	patternVector.push_back(patternSynonym);
	patternVector.push_back(leftType);
	patternVector.push_back(leftArg);
	patternVector.push_back(rightType);
	patternVector.push_back(rightArg);
}

std::pair <std::string, std::string> PatternClause::getPatternPair() {
	return std::pair <std::string, std::string>(patternVector[0], patternVector[1]);
}

std::pair <std::string, std::string> PatternClause::getLeftPair() {
	return std::pair <std::string, std::string>(patternVector[2], patternVector[3]);
}

std::pair <std::string, std::string> PatternClause::getRightPair() {
	return std::pair <std::string, std::string>(patternVector[4], patternVector[5]);
}

PatternClause::~PatternClause() {}
