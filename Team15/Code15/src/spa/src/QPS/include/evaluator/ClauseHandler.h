//
// Created by Jinxin Zhao on 3/2/23.
//
#include "pkb/include/PKB.h"
#include "QPS/include/model/ResultTable.h"
#include "Utility.h"
#include "QPS/include/model/Result.h"


#ifndef SPA_CLAUSEHANDLER_H
#define SPA_CLAUSEHANDLER_H

class ClauseHandler
{
public:    
    PKB pkb;
    ClauseHandler(PKB &pkb);
    void combineResult(ResultTable& resultTable, Result& result);
    void resultTableCheckAndAdd(string arg, ResultTable& resultTable, string DeType);
    std::set<std::string> getResultFromPKB(PKB& pkb, string DeType);
    

    void combineTwoSynResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable);
    void filterCurrResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable);
    void filterResultTable(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, ResultTable& resultTable);
    void filterCurrResultLinkageSet(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable);
    void filterResultTableLinkageSet(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, std::string secondSynonymName, ResultTable& resultTable);
    /*void filterOneSynWithLinkage(std::string synName, std::unordered_map<std::string, SynonymLinkageMap>& synValue, std::string linkedSynName, ResultTable& resultTable);
    void filterOneSynLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, std::string secondSynName, ResultTable& resultTable);*/

    void combineOneSynResult(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable);
    //void mergeResultToTable(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable);
    void deleteSynTableEntry(std::string synonymName, std::string key, ResultTable& resultTable);
    void deleteLinkageInTable(std::string synName, std::string synValue, std::string linkedSyn, std::string linkedSynValue, ResultTable& resultTable);
    
    
    
    

private:
};

#endif // SPA_CLAUSEHANDLER_H
