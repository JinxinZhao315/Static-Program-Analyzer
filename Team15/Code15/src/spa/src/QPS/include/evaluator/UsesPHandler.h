#include "ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>

#ifndef SPA_USESPHANDLER_H
#define SPA_USESPHANDLER_H


class UsesPHandler : public ClauseHandler {
public:
    explicit UsesPHandler(PKB& pkb);
//    Result evalUsesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    Result evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) override;
};
#endif 