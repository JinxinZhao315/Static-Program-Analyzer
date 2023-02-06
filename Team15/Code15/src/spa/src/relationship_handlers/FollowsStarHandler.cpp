//
// Created by Jinxin Zhao on 5/2/23.
//

#include "FollowsStarHandler.h"

FollowsStarHandler::FollowsStarHandler(PKB& pkb) : ClauseHandler(pkb) {}

Result FollowsStarHandler::evalFollowsStar(SuchThatClause suchThatClause, ResultTable& resultTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    // Wildcard-Wildcard
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isFollowEmpty; // = pkb.isFollowEmpty()
        if (isFollowEmpty) {
            result.setResultTrue(false);
            return result;
        }
        // Wildcard-Int
    } else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
        std::set<int> leaderSet; // = pkb.getFollowsStarLeaderNums(stoi(rightArg))
        if (leaderSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Wildcard
    } else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        std::set<int> followerSet; // = pkb.getFollowsStarFollowerNums(stoi(leftArg))
        if (followerSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Int
    } else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isFollow; // =pkb.areInFollowsStarRelationship(leftArg, rightArg)
        if (!isFollow) {
            result.setResultTrue(false);
            return result;
        }
        // Synon - Wildcard/Int
    } else if (leftType == Utility::SYNONYM && rightType != Utility::SYNONYM) {
        resultTableCheckAndAdd(leftArg, resultTable);
        std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);
        std::set<string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (string currSynonVal: currSynonValues) {
                std::set<int> followerSet; //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!followerSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (rightType == Utility:: INTEGER) {
            for (string currSynonVal: currSynonValues) {
                bool isRightFollowStarLeft; //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
                if (isRightFollowStarLeft) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setLeftArg(leftArg, resultSynonValues);

        // Wilcard/Int - Synon
    } else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        resultTableCheckAndAdd(rightArg, resultTable);
        std::set<string> currSynonValues = resultTable.getValueFromKey(rightArg);
        std::set<string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (string currSynonVal: currSynonValues) {
                std::set<int> leaderSet; //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!leaderSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (leftType == Utility::INTEGER) {
            for (string currSynonVal: currSynonValues) {
                bool isRightFollowStarLeft; //=pkb.areInFollowsStarRelationship(leftArg, currSynonVal)
                if (isRightFollowStarLeft) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setRightArg(rightArg, resultSynonValues);
        // Synon - Synon
    } else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        resultTableCheckAndAdd(leftArg, resultTable);
        resultTableCheckAndAdd(rightArg, resultTable);
        std::set<string> currLeftValues = resultTable.getValueFromKey(leftArg);
        std::set<string> currRightValues = resultTable.getValueFromKey(rightArg);

        std::set<string> leftResultValues;
        std::set<string> rightResultValues;

        for (string currLeftVal: currLeftValues) {
            for (string currRightVal: currRightValues) {
                bool isRightFollowStarLeft; //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
                if (isRightFollowStarLeft) {
                    leftResultValues.insert(currLeftVal);
                    rightResultValues.insert(currRightVal);
                }
            }
        }

        if (leftResultValues.empty() || rightResultValues.empty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setLeftArg(leftArg, leftResultValues);
        result.setRightArg(rightArg, rightResultValues);
    } else {
        throw std::runtime_error("Unhandled left or right arg type in FollowsHandler");
    }


    return result;


}