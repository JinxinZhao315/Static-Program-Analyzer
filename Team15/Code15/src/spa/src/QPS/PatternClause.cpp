#include "PatternClause.h"

PatternClause::PatternClause() {}

PatternClause::PatternClause(std::string patternSynonym,
    std::string leftArg, std::string rightArg) {
    this->patternSynonym = patternSynonym;
    this->leftArg = leftArg;
    this->rightArg = rightArg;
}



std::string PatternClause::getPatternSynonym() {
    return this->patternSynonym;
}

std::string PatternClause::getLeftArg() {
    return this->leftArg;
}

std::string PatternClause::getRightArg() {
    return this->rightArg;
}

PatternClause::~PatternClause() {}
