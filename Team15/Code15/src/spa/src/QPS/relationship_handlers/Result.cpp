//
// Created by Jinxin Zhao on 3/2/23.
//

#include "Result.h"

bool Result::isResultTrue() {
    return this->isTrue;
}

void Result::setResultTrue(bool isTrueValue) {
    this->isTrue = isTrueValue;
}

//getter and setter for left arg
std::string Result::getFirstArgName() {
    return this->firstArgName;
};
std::set<std::string> Result::getFirstArgValue() {
    return this->firstArgValue;
};
void Result::setFirstArg(std::string name, std::set<std::string> value) {
    this->firstArgName = name;
    this->firstArgValue = value;
    this->isfirstArgAvailable = true;
}

bool Result::isFirstArgSynonym() {
    return this->isfirstArgAvailable;
}

//getter and setter for right arg
std::string Result::getSecondArgName() {
    return this->secondArgName;
};
std::set<std::string> Result::getSecondArgValue() {
    return this->secondArgValue;
};

void Result::setSecondArg(std::string name, std::set<std::string> value) {
    this->secondArgName = name;
    this->secondArgValue = value;
    this->isSecondArgAvailable = true;
}
bool Result::isSecondArgSynonym() {
    return this->isSecondArgAvailable;
}