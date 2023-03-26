#include "QPS/include/evaluator/FollowsHandler.h"

FollowsHandler::FollowsHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> FollowsHandler::getFollowsFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_LEADER) {
            int leader = pkb.getFollowsLeaderNum(stoi(arg), -1);
            //if leader does not exist, return -1
            if (leader != -1) {
                ret.insert(leader);
            }
        } else { //if (type == GET_FOLLOWER)
            int follower = pkb.getFollowsFollowerNum(stoi(arg), -1);
            //if follower does not exist, return -1
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

Result FollowsHandler::evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
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
        std::set<int> leaderSet = getFollowsFromPKB(isStar, GET_LEADER, rightArg);
        if (leaderSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Wildcard
    } else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, leftArg);
        if (followerSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Int
    } else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isFollow = getIsFollowsFromPKB(isStar, leftArg, rightArg);
        if (!isFollow) {
            result.setResultTrue(false);
            return result;
        }
        // Synon - Wildcard/Int
    } else if (leftType == Utility::SYNONYM && rightType != Utility::SYNONYM) {

        string synonDeType = synonymTable.find(leftArg)->second;
        std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (auto currSynonVal: currSynonValues) {
                std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, currSynonVal);
                if (!followerSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        } else if (rightType == Utility:: INTEGER) {
            for (auto currSynonVal : currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currSynonVal, rightArg);
                if (isRightFollowLeft) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
        // Wilcard/Int - Synon
    } else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {

        string synonDeType = synonymTable.find(rightArg)->second;
        std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (auto currSynonVal : currSynonValues) {
                std::set<int> leaderSet = getFollowsFromPKB(isStar, GET_LEADER, currSynonVal);
                if (!leaderSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (leftType == Utility::INTEGER) {
            for (auto currSynonVal : currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, leftArg, currSynonVal);
                if (isRightFollowLeft) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
        // Synon - Synon
    } 
    else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        if (leftArg == rightArg) {
            result.setResultTrue(false);
            return result;
        }
        std::string leftDeType = synonymTable.find(leftArg)->second;
        std::string rightDeType = synonymTable.find(rightArg)->second;

        std::set<string> leftSynValuesStrSet = Utility::getFullSetFromPkb(pkb, leftDeType);
		std::set<string> rightSynValuesStrSet = Utility::getFullSetFromPkb(pkb, rightDeType);

		std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
		std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());


        ResultTable initTable(currLeftValues, leftArg);
        initTable.combineTable(ResultTable(currRightValues, rightArg));
        int initTableSize = initTable.getColNum();

        ResultTable tempTable({ leftArg, rightArg });

        for (int i = 0; i < initTableSize; i++) {
            std::vector<std::string> tuple = initTable.getTuple(i);
            bool isRightFollowLeft = getIsFollowsFromPKB(isStar, tuple[0], tuple[1]);
            if (isRightFollowLeft) {
                tempTable.insertTuple({ tuple[0], tuple[1] });
            }
        }

        if (tempTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setClauseResult(tempTable);
    } else {
        throw std::runtime_error("Unhandled left or right arg type in FollowsHandler");
    }


    return result;


}