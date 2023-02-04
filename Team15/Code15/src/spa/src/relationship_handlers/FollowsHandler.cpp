//
// Created by Jinxin Zhao on 3/2/23.
//

#include "FollowsHandler.h"

FollowsHandler::FollowsHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result FollowsHandler::evalFollows(SuchThatClause suchThatClause) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    // Wildcard-Wildcard
    if (leftType ==  "_" && rightArg == "_") {
        bool isFollowEmpty; // = pkb.isFollowEmpty()
        if (isFollowEmpty) {
            result.setResultTrue(false);
        } else {
            result.setResultTrue(true);
        }
        return result;
    } else if () {

    }
    // TODO: add other cases

}