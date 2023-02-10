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
    ClauseHandler(PKB &pkb);
    void combineResult(ResultTable& resultTable, Result& result);
    std::set<std::string> getResultFromPKB(PKB& pkb, string DeType);
    void resultTableCheckAndAdd(string arg, ResultTable& resultTable, string DeType);
    PKB pkb;
private:
    void combine(std::string synonymName, std::set<std::string>& synonymSet, ResultTable& resultTable);
//    template <typename T>
//    std::set<T> convertVecToSet(std::vector<T> vec);

};

#endif // SPA_CLAUSEHANDLER_H
