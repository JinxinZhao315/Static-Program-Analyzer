//
// Created by Jinxin Zhao on 3/2/23.
//

#include "FollowsHandler.h"

FollowsHandler::FollowsHandler(PKB pkb, ResultTable resultTable) : ClauseHandler(pkb, resultTable) {}

Result FollowsHandler::evalFollows(SuchThatClause suchThatClause) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    Result result;
    // Wildcard-Wildcard
    if (leftArg == "_" && rightArg == "_") {
        bool isFollowEmpty; // = pkb.isFollowEmpty()
        if (isFollowEmpty) {
            result.setResultTrue(false);
        } else {
            result.setResultTrue(true);
        }
        return result;
    }
    // TODO: add other cases

}