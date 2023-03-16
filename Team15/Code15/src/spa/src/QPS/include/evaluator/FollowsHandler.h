#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_FOLLOWSSTARHANDLER_H
#define SPA_FOLLOWSSTARHANDLER_H


class FollowsHandler : public ClauseHandler{
public:
    explicit FollowsHandler(PKB& pkb);
//    Result evalFollows(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    Result evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) override;
private:
    string GET_LEADER = "get_leader";
    string GET_FOLLOWER = "get_follower";
    std::set<int> getFollowsFromPKB(bool isStar, string type, string arg);
    bool getIsFollowsFromPKB(bool isStar, string leftArg, string rightArg);
};


#endif //SPA_FOLLOWSSTARHANDLER_H
