#include "qps/include/model/PatternClause.h"

PatternClause::PatternClause() : Clause(PATTERN){}

PatternClause::PatternClause(std::string patternSynonym,
    std::string firstArg, std::string secondArg, std::string thrirdArg) : Clause(PATTERN) {
    this->patternSynonym = patternSynonym;
    addSyn(patternSynonym);
    this->firstArg = firstArg;
    if (Utility::getEnumReferenceType(firstArg) == SYNONYM) {
        addSyn(firstArg);
    }
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
