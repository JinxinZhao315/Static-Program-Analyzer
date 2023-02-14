#include "QPS/include/evaluator/FollowsHandler.h"

FollowsHandler::FollowsHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> FollowsHandler::getFollowsFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_LEADER) {
            int leader = pkb.getFollowsLeaderNum(stoi(arg)); //
            if (leader != NULL) {
                ret.insert(leader);
            }
        } else { //if (type == GET_FOLLOWER)
            int follower = pkb.getFollowsFollowerNum(stoi(arg));//
            if (follower != NULL) {
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
        std::unordered_map<std::string, SynonymLinkageMap> currSynonValues = resultTable.getSynonymEntry(leftArg);
        std::unordered_map<std::string, SynonymLinkageMap> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            //currSynonVal: (string synonymValue, SynonymLinkageMap) pair
            for (auto currSynonVal: currSynonValues) {
                std::set<int> followerSet = getFollowsFromPKB(isStar, GET_FOLLOWER, currSynonVal.first); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!followerSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (rightType == Utility:: INTEGER) {
            for (auto currSynonVal : currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currSynonVal.first, rightArg); //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
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
        std::unordered_map<std::string, SynonymLinkageMap> currSynonValues = resultTable.getSynonymEntry(rightArg);
        std::unordered_map<std::string, SynonymLinkageMap> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (auto currSynonVal: currSynonValues) {
                std::set<int> leaderSet = getFollowsFromPKB(isStar, GET_LEADER, currSynonVal.first); //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!leaderSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        } else if (leftType == Utility::INTEGER) {
            for (auto currSynonVal: currSynonValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, leftArg, currSynonVal.first); //=pkb.areInFollowsStarRelationship(leftArg, currSynonVal)
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

        set<string> currLeftValues = resultTable.getStringSetFromKey(leftArg);
        set<string> currRightValues = resultTable.getStringSetFromKey(rightArg);
        std::unordered_map<std::string, SynonymLinkageMap> leftResultValues;
        std::unordered_map<std::string, SynonymLinkageMap> rightResultValues;

        for (auto currLeftVal: currLeftValues) {
            for (auto currRightVal: currRightValues) {
                bool isRightFollowLeft = getIsFollowsFromPKB(isStar, currLeftVal, currRightVal); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
                if (isRightFollowLeft) {
                    if (leftResultValues.find(currLeftVal) == leftResultValues.end()) {
                        SynonymLinkageMap leftLinkedSynonymCollection;
                        leftLinkedSynonymCollection.insertLinkage(rightArg, currRightVal);
                        leftResultValues.insert(std::make_pair<>(currLeftVal, leftLinkedSynonymCollection));
                    }
                    else {
                        leftResultValues.find(currLeftVal)->second
                            .insertLinkage(rightArg, currRightVal);
                    }

                    if (rightResultValues.find(currRightVal) == rightResultValues.end()) {
                        SynonymLinkageMap rightLinkedSynonymCollection;
                        rightLinkedSynonymCollection.insertLinkage(leftArg, currLeftVal);
                        rightResultValues.insert(std::make_pair<>(currRightVal, rightLinkedSynonymCollection));
                    }
                    else {
                        rightResultValues.find(currRightVal)->second
                            .insertLinkage(leftArg, currLeftVal);
                    }
                    
                    //leftResultValues.insert(currLeftVal);
                    //rightResultValues.insert(currRightVal);
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