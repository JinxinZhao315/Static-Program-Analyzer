//
// Created by Jinxin Zhao on 3/2/23.
//
#include "PKB.h"
#include "Tokens.h"
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
    std::set<std::string> getResultFromPKB(PKB& pkb, string DeType);
    void resultTableCheckAndAdd(string arg, ResultTable& resultTable, string DeType);

    void combineTwoSynResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult,
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable& resultTable);
    void combineOneSynResult(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable);
    //void mergeResultToTable(std::string synonymName, std::unordered_map<std::string, SynonymLinkageMap>& currResult, ResultTable& resultTable);
    void deleteSynTableEntry(std::string synonymName, std::string key, ResultTable& resultTable);
    void deleteLinkage(std::string linkedSynonym, std::string linkedSynonymInstance,
        std::string synonymName, std::string synonymInstance, ResultTable& resultTable);
    void filterCurrResult(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, 
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable &resultTable);
    void filterResultTable(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, ResultTable &resultTable);
    void filterCurrResultLinkageSet(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, 
        std::string secondSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& secondSynResult, ResultTable &resultTable);
    void filterResultTableLinkageSet(std::string firstSynonymName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, std::string secondSynonymName, ResultTable &resultTable);
    void filterOneSynToResult(std::string synName, std::unordered_map<std::string, SynonymLinkageMap>& synValue, std::string linkedSynName, ResultTable& resultTable);
    void filterOneSynLinkageSet(std::string firstSynName, std::unordered_map<std::string, SynonymLinkageMap>& firstSynResult, std::string secondSynName, ResultTable& resultTable);
private:
};

#endif // SPA_CLAUSEHANDLER_H
