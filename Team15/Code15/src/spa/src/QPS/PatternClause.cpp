#include "PatternClause.h"

PatternClause::PatternClause() {}

PatternClause::PatternClause(std::string patternType, std::string patternSynonym,
    std::string leftArg, std::string rightArg) {
    this->patternType = patternType;
    this->patternSynonym = patternSynonym;
    this->leftArg = leftArg;
    this->rightArg = rightArg;
}

std::pair <std::string, std::string> PatternClause::getPatternPair() {
    return std::pair <std::string, std::string>(this->patternType, this->patternType);
}

std::string PatternClause::getLeftArg() {
    return this->leftArg;
}

std::string PatternClause::getRightArg() {
    return this->rightArg;
}

PatternClause::~PatternClause() {}
