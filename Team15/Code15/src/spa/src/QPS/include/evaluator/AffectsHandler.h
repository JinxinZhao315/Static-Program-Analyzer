#include "ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#include <queue>
#ifndef SPA_AffectsHANDLER_H
#define SPA_AffectsHANDLER_H


class AffectsHandler : public ClauseHandler {
public:
    explicit AffectsHandler(PKB& pkb);
    //    Result evalAffects(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    Result evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) override;

private:
    string GET_LEADER = "get_leader";
    string GET_FOLLOWER = "get_follower";
    std::set<int> getAffectsFromPKB(bool isStar, string type, string arg);
    bool getIsAffectsFromPKB(bool isStar, string leftArg, string rightArg);
    bool isAffectsEmptyFromPKB(bool isStar);
};


#endif