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
    /*std::unordered_map<std::string, 
        std::unordered_map<std::string, SynonymLinkageMap>> resultTable;*/
    std::vector<std::vector<std::string>> resultTable;
    std::vector<std::string> synList;
    int colNum;
    // e.g. stmt s1, s2
    // {s1: values{10: {s2: values{11, 12, 13}
    //                  }
    //            }
    //  }
public:
    ResultTable();

    ResultTable(std::vector<std::vector<std::string>> resultTable, std::vector<std::string> synList);
    
    void combineTable(ResultTable resultTable);

    bool isSynonymPresent(std::string key);

    void setSynList(std::vector<std::string> synList);

    int getSizeOfResultTable();

    bool isTableEmpty();

    bool isValidMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    void deleteTuple(int index);
    
    std::vector<std::string> mergeTuple(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    void insertTuple(std::vector<std::string> tuple) {
        if (tuple.size() == colNum) {
            resultTable.push_back(tuple);
        }
    }

    std::vector<std::vector<std::string>> getResultTable();

    std::vector<std::string> getSynList();

    //void insertKeyValuePair(std::string key, std::set<std::string> value);
    //std::unordered_map<std::string, SynonymLinkageMap>& getSynonymEntry(std::string key);
    //void deleteKeyValuePair(std::string key);
    //void resetKeySetEmpty(std::string);
    //bool isKeyPresent(std::string key);

    //std::set<std::string> getStringSetFromKey(std::string synonymName);
    //void deleteSynonymInstance(std::string synonymName, std::string synonymInstance);
    //bool existSynonymWithNoValue();
};


#endif //SPA_RESULTTABLE_H
