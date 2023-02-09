#include "FollowsHandler.h"

FollowsHandler::FollowsHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> FollowsHandler::getFollowsFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_LEADER) {
            int leader = pkb.getFollowsLeaderNum(stoi(arg)); //
            if (leader != -1) {
                ret.insert(leader);
            }
        } else { //if (type == GET_FOLLOWER)
            int follower = pkb.getFollowsFollowerNum(stoi(arg));//
            if (follower != -1) {
                ret.insert(follower);
            }
        }
    } else {
        if (type == GET_LEADER) {
            ret = pkb.getFollowsStarLeaderNums(stoi(arg));
        } else { //  if (type == GET_FOLLOWER)
            ret = pkb.getFollowsStarFollowerNums(stoi(arg));
        }
    }
    return ret;
}

bool FollowsHandler:: getIsFollowsFromPKB(bool isStar, string leftArg, string rightArg) {
    bool ret;
    if (isStar) {
        ret =pkb.areInFollowsStarRelationship(stoi(leftArg), stoi(rightArg));
    } else {
        ret =pkb.areInFollowsRelationship(stoi(leftArg), stoi(rightArg));
    }
    return ret;
}

Result FollowsHandler::evalFollows(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    // Wildcard-Wildcard
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isFollowEmpty = pkb.isFollowsEmpty(); //
        if (isFollowEmpty) {
            result.setResultTrue(false);
            return result;
        }
        // Wildcard-Int
    } else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
        std::set<int> leaderSet = getFollowsFromPKB(isStar, GET_LEADER, rightArg); // = pkb.getFollowsStarLeaderNums(stoi(rightArg))
        if (leaderSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Wildcard
    } else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, leftArg); // = pkb.getFollowsStarFollowerNums(stoi(leftArg))
        if (followerSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Int
    } else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isFollow = getIsFollowsFromPKB(isStar, leftArg, rightArg); // =pkb.areInFollowsStarRelationship(leftArg, rightArg)
        if (!isFollow) {
            result.setResultTrue(false);
            return result;
        }
        // Synon - Wildcard/Int
    } else if (leftType == Utility::SYNONYM && rightType != Utility::SYNONYM) {
        string synonDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
        std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);

        std::set<string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (string currSynonVal: currSynonValues) {
                std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, currSynonVal); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!followerSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (rightType == Utility:: INTEGER) {
            for (string currSynonVal: currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currSynonVal, rightArg); //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
                if (isRightFollowLeft) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setFirstArg(leftArg, resultSynonValues);

        // Wilcard/Int - Synon
    } else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string synonDeType = synonymTable.find(rightArg)->second;
        resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
        std::set<string> currSynonValues = resultTable.getValueFromKey(rightArg);
        std::set<string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (string currSynonVal: currSynonValues) {
                std::set<int> leaderSet = getFollowsFromPKB(isStar, GET_LEADER, currSynonVal); //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!leaderSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (leftType == Utility::INTEGER) {
            for (string currSynonVal: currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, leftArg, currSynonVal); //=pkb.areInFollowsStarRelationship(leftArg, currSynonVal)
                if (isRightFollowLeft) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setSecondArg(rightArg, resultSynonValues);
        // Synon - Synon
    } else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string leftDeType = synonymTable.find(leftArg)->second;
        string rightDeType = synonymTable.find(rightArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
        std::set<string> currLeftValues = resultTable.getValueFromKey(leftArg);
        std::set<string> currRightValues = resultTable.getValueFromKey(rightArg);

        std::set<string> leftResultValues;
        std::set<string> rightResultValues;

        for (string currLeftVal: currLeftValues) {
            for (string currRightVal: currRightValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currLeftVal, currRightVal); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
                if (isRightFollowLeft) {
                    leftResultValues.insert(currLeftVal);
                    rightResultValues.insert(currRightVal);
                }

            }
        }

        if (leftResultValues.empty() || rightResultValues.empty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setFirstArg(leftArg, leftResultValues);
        result.setSecondArg(rightArg, rightResultValues);
    } else {
        throw std::runtime_error("Unhandled left or right arg type in FollowsHandler");
    }


    return result;


}