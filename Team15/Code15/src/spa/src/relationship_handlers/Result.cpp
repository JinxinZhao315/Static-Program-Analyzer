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
std::string Result::getLeftArgName() {
    return this->leftArgName;
};
std::set<std::string> Result::getLeftArgValue() {
    return this->leftArgValue;
};
void Result::setLeftArg(std::string name, std::set<std::string> value) {
    this->leftArgName = name;
    this->leftArgValue = value;
    this->isLeftArgAvailable = true;
}

bool Result::isLeftArgSynonym() {
    return this->isLeftArgAvailable;
}

//getter and setter for right arg
std::string Result::getRightArgName() {
    return this->rightArgName;
};
std::set<std::string> Result::getRightArgValue() {
    return this->rightArgValue;
};

void Result::setRightArg(std::string name, std::set<std::string> value) {
    this->rightArgName = name;
    this->rightArgValue = value;
    this->isRightArgAvailable = true;
}
bool Result::isRightArgSynonym() {
    return this->isRightArgAvailable;
}