//
// Created by Jinxin Zhao on 5/2/23.
//
#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "SuchThatClause.h"
#include <string>
#include <set>
#ifndef SPA_FOLLOWSSTARHANDLER_H
#define SPA_FOLLOWSSTARHANDLER_H


class FollowsStarHandler : public ClauseHandler{
public:
    FollowsStarHandler(PKB& pkb);
    Result evalFollowsStar(SuchThatClause suchThatClause, ResultTable& resultTable);

};


#endif //SPA_FOLLOWSSTARHANDLER_H
