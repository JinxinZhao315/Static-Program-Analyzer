#include "ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#include <queue>
#ifndef SPA_NEXTHANDLER_H
#define SPA_NEXTHANDLER_H


class NextHandler : public ClauseHandler {
public:
    NextHandler(PKB& pkb);
    Result evalNext(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    std::set<int> getNextFromPKB(bool isStar, string type, string arg);
    bool getIsNextFromPKB(bool isStar, string leftArg, string rightArg);
    bool isNextEmptyFromPKB(bool isStar);
private:
    string GET_LEADER = "get_leader";
    string GET_FOLLOWER = "get_follower";
};


#endif 
