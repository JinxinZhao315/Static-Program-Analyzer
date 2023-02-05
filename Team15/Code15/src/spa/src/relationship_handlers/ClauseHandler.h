//
// Created by Jinxin Zhao on 3/2/23.
//
#include "PKB.h"
#include "ResultTable.h"
#include "Utility.h"
#include "Result.h"

#ifndef SPA_CLAUSEHANDLER_H
#define SPA_CLAUSEHANDLER_H

class ClauseHandler
{
public:
    ClauseHandler(PKB &pkb);

protected:
    void combineResult(ResultTable& resultTable, Result& result);
    std::set<std::string> getResultFromPKB(PKB& pkb, std::string resultType);
private:
    PKB pkb;
    void combine(std::string synonymName, std::set<std::string>synonymSet, ResultTable& resultTable);
    template <typename T>
    std::set<T> convertVecToSet(std::vector<T> vec);
};

#endif // SPA_CLAUSEHANDLER_H
