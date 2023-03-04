#include "QPS/include/model/PatternClause.h"

PatternClause::PatternClause() {}

PatternClause::PatternClause(std::string patternSynonym,
    std::string firstArg, std::string secondArg, std::string thrirdArg) {
    this->patternSynonym = patternSynonym;
    this->firstArg = firstArg;
    this->secondArg = secondArg;
    this->thirdArg = thrirdArg;
}


std::string PatternClause::getPatternSynonym() {
    return this->patternSynonym;
}

std::string PatternClause::getFirstArg() {
    return this->firstArg;
}

std::string PatternClause::getSecondArg() {
    return this->secondArg;
}

std::string PatternClause::getThirdArg() {
    return this->thirdArg;
}

PatternClause::~PatternClause() {}
