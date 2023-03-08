#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_CALLSSTARHANDLER_H
#define SPA_CALLSSTARHANDLER_H


class CallsHandler : public ClauseHandler {
public:
    CallsHandler(PKB& pkb);
    Result evalCalls(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    std::set<int> getCallsFromPKB(bool isStar, string type, string arg);
    bool getIsCallsFromPKB(bool isStar, string leftArg, string rightArg);
};


#endif //SPA_CALLSSTARHANDLER_H