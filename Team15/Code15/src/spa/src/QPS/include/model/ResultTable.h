//
// Created by Jinxin Zhao on 3/2/23.
//
#include <unordered_map>
#include <string>
#include <set>
#include <assert.h>
#include "SynonymLinkageMap.h"
#include "pkb/include/PKB.h"
#include "Elem.h"
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


    void clearResultTable();

    bool isSynExist(std::string synName);

    bool isTupleMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    void deleteTuple(int index);

    void insertTuple(std::vector<std::string> tuple);

    std::vector<std::string> mergeTuple(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    std::vector<std::string> getTuple(int index);

    std::set<std::string> getSelectedResult(std::vector<Elem> selectedElem, PKB &pkb, bool isEarlyExit);

    std::string getAttrRefValue(int synIndex, int colIndex, AttrRef attrRef, PKB &pkb);
};


#endif //SPA_RESULTTABLE_H
