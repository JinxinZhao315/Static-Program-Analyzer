#include "QPS/include/model/Result.h"

bool Result::isResultTrue() {
    return this->isTrue;
}

void Result::setResultTrue(bool isTrueValue) {
    this->isTrue = isTrueValue;
}

ResultTable Result::getClauseResult() {
    return this->clauseResult;
}

void Result::setClauseResult(ResultTable tempResult) {
    this->clauseResult = tempResult;
}