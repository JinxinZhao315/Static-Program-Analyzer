//
// Created by Jinxin Zhao on 3/2/23.
//

#include "ResultTable.h"
ResultTable::ResultTable() {}

bool ResultTable::isKeyPresent(std::string key) {
    if (this->resultTable.find(key) == this->resultTable.end()) {
        return false;
    } else {
        return true;
    }
}

std::set<std::string> ResultTable::getValueFromKey(std::string key) {
    return this->resultTable.at(key);
}



void ResultTable::insertKeyValuePair(std::string key, std::set<std::string> value) {
    this->resultTable.insert({key, value});
}

int ResultTable::sizeOfResultTable() {
    return resultTable.size();
} 

void ResultTable::deleteKeyValuePair(std::string key) {
    this->resultTable.erase(key);
}