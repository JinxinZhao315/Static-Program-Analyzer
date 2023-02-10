//
// Created by Jinxin Zhao on 3/2/23.
//
#include <unordered_map>
#include <string>
#include <set>
#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H


class ResultTable {
private:
    std::unordered_map<std::string, std::set<std::string>> resultTable;
public:
    ResultTable();
    bool isKeyPresent(std::string key);
    void insertKeyValuePair(std::string key, std::set<std::string> value);
    std::set<std::string> getValueFromKey(std::string key);
    int sizeOfResultTable();
    void deleteKeyValuePair(std::string key);
    void resetKeySetEmpty(std::string);
};


#endif //SPA_RESULTTABLE_H
