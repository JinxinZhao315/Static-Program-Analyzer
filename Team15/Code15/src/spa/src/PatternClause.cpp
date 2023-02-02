#include "PatternClause.h"

PatternClause::PatternClause() {}

PatternClause::PatternClause(std::string patternType, std::string patternSynonym, std::string leftType,
	std::string leftArg, std::string rightType, std::string rightArg) {
    this->patternType = patternType;
    this->patternSynonym = patternSynonym;
    this->leftType = leftType;
    this->leftArg = leftArg;
    this->rightType = rightType;
    this->rightArg = rightArg;
}

std::pair <std::string, std::string> PatternClause::getPatternPair() {
    return std::pair <std::string, std::string>(this->patternType, this->patternType);
}

std::pair <std::string, std::string> PatternClause::getLeftPair() {
    return std::pair <std::string, std::string>(this->leftType, this->leftArg);
}

std::pair <std::string, std::string> PatternClause::getRightPair() {
    return std::pair <std::string, std::string>(this->rightType, this->rightArg);
}

PatternClause::~PatternClause() {}
