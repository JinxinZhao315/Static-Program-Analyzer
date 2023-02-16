#include "ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>

#ifndef SPA_USESSHANDLER_H
#define SPA_USESSHANDLER_H


class UsesSHandler : public ClauseHandler {
public:
    UsesSHandler(PKB& pkb);
    Result evalUsesS(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
};
#endif 