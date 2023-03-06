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
    int rowNum;
    // synList:      <a, b, c>
    //resultTable:: <<1, 2, 3>,
    //               <4, 5, 6>,
    //               <7, 8, 9>>
public:
    ResultTable();

    //result table with no tuple but some synonym
    ResultTable(std::vector<std::string> synList);

    //result table with one synonym and some values
    ResultTable(std::vector<std::string> synResult, std::string synName);

    //result table with multi synonyms and multi tuples
    ResultTable(std::vector<std::vector<std::string>> resultTable, std::vector<std::string> synList);

    int getRowNum();

    int getColNum();



    //void setSynList(std::vector<std::string> synList);

    //void setResultTable(std::vector<std::vector<std::string>> resultTable);
    
    std::vector<std::string> getSynList();

    void combineTable(ResultTable resultTable);

    bool isTableEmpty();

    bool isSynListEmpty();

    std::vector<std::vector<std::string>> getResultTable();

    std::vector<std::string> getSynValues(std::string synName);

    std::set<std::string> getStringSetFromKey(std::string synName);

    void clearResultTable();

    bool isSynExist(std::string synName);

    bool isTupleMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    void deleteTuple(int index);

    void insertTuple(std::vector<std::string> tuple);

    std::vector<std::string> mergeTuple(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    std::vector<std::string> getTuple(int index);


    //bool isSynonymPresent(std::string key);

    

    //int getSizeOfResultTable();

    

    
    


    

    

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
