//
// Created by Jinxin Zhao on 3/2/23.
//
#include <unordered_map>
#include <string>
#include <set>
#include <assert.h>
#include "SynonymLinkageMap.h"
#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H


class ResultTable {
private:
    std::unordered_map<std::string, 
        std::unordered_map<std::string, SynonymLinkageMap>> resultTable;
    // e.g. stmt s1, s2
    // {s1: values{10: {s2: values{11, 12, 13}
    //                  }
    //            }
    //  }
public:
    ResultTable();
    ResultTable(std::unordered_map<std::string, std::unordered_map<std::string, SynonymLinkageMap>> resultTable);
    void insertSynonymEntry(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap> intermediateResult);
    bool isSynonymPresent(std::string key);

    //void insertKeyValuePair(std::string key, std::set<std::string> value);
    std::unordered_map<std::string, SynonymLinkageMap>& getSynonymEntry(std::string key);
    int sizeOfResultTable();
    //void deleteKeyValuePair(std::string key);
    //void resetKeySetEmpty(std::string);
    bool isKeyPresent(std::string key);

    std::set<std::string> getStringSetFromKey(std::string synonymName);
    void deleteSynonymInstance(std::string synonymName, std::string synonymInstance);
};


#endif //SPA_RESULTTABLE_H
