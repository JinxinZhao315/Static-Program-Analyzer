//
// Created by Jinxin Zhao on 3/2/23.
//

#include "QPS/include/model/Result.h"

bool Result::isResultTrue() {
    return this->isTrue;
}

void Result::setResultTrue(bool isTrueValue) {
    this->isTrue = isTrueValue;
}

//getter for left arg
std::string Result::getFirstArgName() {
    return this->firstArgName;
}

bool Result::isFirstArgSynonym() {
    return this->isFirstArgAvailable;
}

//std::unordered_map<std::string, SynonymLinkageMap> Result::getFirstArgValue() {
//    return this->firstArgValue;
//};
//void Result::setFirstArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value) {
//    this->firstArgName = name;
//    this->firstArgValue = value;
//    this->isFirstArgAvailable = true;
//}

ResultTable Result::getClauseResult() {
    return this->clauseResult;
}


//getter and setter for right arg
std::string Result::getSecondArgName() {
    return this->secondArgName;
}

bool Result::isSecondArgSynonym() {
    return this->isSecondArgAvailable;
}
//std::unordered_map<std::string, SynonymLinkageMap> Result::getSecondArgValue() {
//    return this->secondArgValue;
//};

//void Result::setSecondArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value) {
//    this->secondArgName = name;
//    this->secondArgValue = value;
//    this->isSecondArgAvailable = true;
//}



void Result::setClauseResult(bool isFirstArgAvailable, bool isSecondArgAvailable, ResultTable tempResult) {
    this->isFirstArgAvailable = isFirstArgAvailable;
    this->isSecondArgAvailable = isSecondArgAvailable;
    this->clauseResult = tempResult;
    int i = 0;
    if (isFirstArgAvailable) {
        firstArgName = tempResult.getSynList()[i];
        i++;
    }
    if (isSecondArgAvailable) {
        secondArgName = tempResult.getSynList()[i];
    }
}