#include "ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_MODIFIESSHANDLER_H
#define SPA_MODIFIESSHANDLER_H


class ModifiesSHandler : public ClauseHandler {
public:
    explicit ModifiesSHandler(PKB& pkb);
    //Result evalModifiesS(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    Result evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable) override;
};


#endif 