//
// Created by Jinxin Zhao on 5/2/23.
//
#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_FOLLOWSSTARHANDLER_H
#define SPA_FOLLOWSSTARHANDLER_H


class FollowsHandler : public ClauseHandler{
public:
    FollowsHandler(PKB& pkb);
    Result evalFollowsStar(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    std::set<int> getFollowsFromPKB(bool isStar, string type, string arg);
    bool getIsFollowsFromPKB(bool isStar, string leftArg, string rightArg);
private:
    string GET_LEADER = "get_leader";
    string GET_FOLLOWER = "get_follower";
};


#endif //SPA_FOLLOWSSTARHANDLER_H
