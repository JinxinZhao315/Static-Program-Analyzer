#include <unordered_map>
#include <string>
#include <set>
#include <assert.h>
#include "common/include/utils/Utility.h"
#include "pkb/include/PKB.h"
#include "Elem.h"
#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H


class ResultTable {
private:
    std::vector<std::vector<std::string>> resultTable;
    std::unordered_map<std::string, std::set<std::string>> synValMap;
    std::vector<std::string> synList;
    int colNum;
    int rowNum;

public:
    ResultTable();

    //result table with no tuple but some synonym
    ResultTable(std::vector<std::string> synList);

    //result table with one synonym and some values
    ResultTable(std::vector<std::string> synResult, std::string synName);

    //result table with multi synonyms and multi tuples
    ResultTable(std::vector<std::vector<std::string>> resultTable, std::vector<std::string> synList);

    int getSynNum();

    int getTupleNum();

    void resultTableCheckAndAdd(string arg, PKB pkb, string DeType);
    
    std::vector<std::string> getSynList();

    void combineTable(ResultTable resultTable);

    bool isTableEmpty();

    bool isSynListEmpty();

    std::vector<std::vector<std::string>> getResultTable();

    std::set<std::string> getSynValues(std::string synName);

    void clearResultTable();

    bool isSynExist(std::string synName);

    bool isTupleMatch(std::vector<std::string> oldTuple, std::vector<std::string> currTuple, std::vector<int> commonSynIndex);

    void insertTuple(std::vector<std::string> tuple);

    std::vector<std::string> getTuple(int index);

    std::set<std::string> getSelectedResult(std::vector<Elem*> selectedElem, PKB &pkb, bool isEarlyExit);

    std::string getAttrRefValue(int synIndex, int colIndex, AttrRef attrRef, PKB &pkb);

    void deleteSynonym(std::string synonym);

    void removeDuplicates();

    bool containsSyn(std::string syn);
};


#endif //SPA_RESULTTABLE_H
