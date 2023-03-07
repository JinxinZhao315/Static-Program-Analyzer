#include "QPS/include/evaluator/ParentHandler.h"

ParentHandler::ParentHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> ParentHandler::getParentFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_PARENT) {
            int parent = pkb.getParentParentNum(stoi(arg), -1);
            //if parent does not exist, return -1
            if (parent != -1) {
                ret.insert(parent);
            }
        }
        else { //if (type == GET_CHILD)
            std::set<int> children = pkb.getParentChildNums(stoi(arg));
            if (!children.empty()) {
                ret.insert(children.begin(), children.end());
            }
        }
    }
    else {
        if (type == GET_PARENT) {
            ret = pkb.getParentStarParentNums(stoi(arg));
        }
        else { //  if (type == GET_CHILD)
            ret = pkb.getParentStarChildNums(stoi(arg));
        }
    }
    return ret;
}

bool ParentHandler::getIsParentFromPKB(bool isStar, string leftArg, string rightArg) {
    bool ret;
    if (isStar) {
        ret = pkb.areInParentStarRelationship(stoi(leftArg), stoi(rightArg));
    }
    else {
        ret = pkb.areInParentRelationship(stoi(leftArg), stoi(rightArg));
    }
    return ret;
}

Result ParentHandler::evalParentStar(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;
    
    // Wildcard-Wildcard
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isParentEmpty = pkb.isParentEmpty(); //
        if (isParentEmpty) {
            result.setResultTrue(false);
            return result;
        }
        // Wildcard-Int
    }
    else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
        std::set<int> parentSet = getParentFromPKB(isStar, GET_PARENT, rightArg); // = pkb.getFollowsStarLeaderNums(stoi(rightArg))
        if (parentSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Wildcard
    }
    else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        std::set<int> childSet = getParentFromPKB(isStar, GET_CHILD, leftArg); // = pkb.getFollowsStarFollowerNums(stoi(leftArg))
    
        if (childSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
        // Int-Int
    }
    else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isParent = getIsParentFromPKB(isStar, leftArg, rightArg); // =pkb.areInFollowsStarRelationship(leftArg, rightArg)
        if (!isParent) {
            result.setResultTrue(false);
            return result;
        }
        // Synon - Wildcard/Int
    }
    else if (leftType == Utility::SYNONYM && rightType != Utility::SYNONYM) {
        string synonDeType = varTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> resultSynonValues;
        //std::unordered_map<std::string, SynonymLinkageMap> currSynonValues = resultTable.getSynonymEntry(leftArg);
        //std::unordered_map<std::string, SynonymLinkageMap> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (auto currSynonVal : currSynonValues) {
                std::set<int> childSet = getParentFromPKB(isStar, GET_CHILD, currSynonVal); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!childSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (rightType == Utility::INTEGER) {
            for (auto currSynonVal : currSynonValues) {
                bool isRightParentStarLeft = getIsParentFromPKB(isStar, currSynonVal, rightArg); //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
                if (isRightParentStarLeft) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(true, false, ResultTable(resultSynonValues, leftArg));

        // Wilcard/Int - Synon
    }
    else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string synonDeType = varTable.find(rightArg)->second;
        resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
        std::vector<std::string> resultSynonValues;
        //std::unordered_map<std::string, SynonymLinkageMap> currSynonValues = resultTable.getSynonymEntry(rightArg);
        //std::unordered_map<std::string, SynonymLinkageMap> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (auto currSynonVal : currSynonValues) {
                std::set<int> parentSet = getParentFromPKB(isStar, GET_PARENT, currSynonVal); //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!parentSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (leftType == Utility::INTEGER) {
            for (auto currSynonVal : currSynonValues) {
                bool isRightParentStarLeft = getIsParentFromPKB(isStar, leftArg, currSynonVal); //=pkb.areInFollowsStarRelationship(leftArg, currSynonVal)
                if (isRightParentStarLeft) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        //result.setSecondArg(rightArg, resultSynonValues);
        result.setClauseResult(false, true, ResultTable(resultSynonValues, rightArg));

        // Synon - Synon
    }
    else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        if (leftArg == rightArg) {
            result.setResultTrue(false);
            return result;
        }
        string leftDeType = varTable.find(leftArg)->second;
        string rightDeType = varTable.find(rightArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        resultTableCheckAndAdd(rightArg, resultTable, rightDeType);

        std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);
        //std::unordered_map<std::string, SynonymLinkageMap> leftResultValues;
        //std::unordered_map<std::string, SynonymLinkageMap> rightResultValues;
        ResultTable tempResultTable({ leftArg, rightArg });

        for (int i = 0; i < currLeftValues.size(); i++) {
            bool isRightParentStarLeft = getIsParentFromPKB(isStar, currLeftValues[i], currRightValues[i]); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
            if (isRightParentStarLeft) {
                tempResultTable.insertTuple({ currLeftValues[i], currRightValues[i] });
            }
        }

        //for (string currLeftVal : currLeftValues) {
        //    for (string currRightVal : currRightValues) {
        //        bool isRightParentStarLeft = getIsParentFromPKB(isStar, currLeftVal, currRightVal); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
        //        if (isRightParentStarLeft) {
        //            tempResultTable.insertTuple({ currLeftVal, currRightVal });

        //           /* if (leftResultValues.find(currLeftVal) == leftResultValues.end()) {
        //                SynonymLinkageMap leftLinkedSynonymCollection;
        //                leftLinkedSynonymCollection.insertLinkage(rightArg, currRightVal);
        //                leftResultValues.insert(std::make_pair<>(currLeftVal, leftLinkedSynonymCollection));
        //            }
        //            else {
        //                leftResultValues.find(currLeftVal)->second
        //                    .insertLinkage(rightArg, currRightVal);
        //            }

        //            if (rightResultValues.find(currRightVal) == rightResultValues.end()) {
        //                SynonymLinkageMap rightLinkedSynonymCollection;
        //                rightLinkedSynonymCollection.insertLinkage(leftArg, currLeftVal);
        //                rightResultValues.insert(std::make_pair<>(currRightVal, rightLinkedSynonymCollection));
        //            }
        //            else {
        //                rightResultValues.find(currRightVal)->second
        //                    .insertLinkage(leftArg, currLeftVal);
        //            }*/
        //        }
        //    }
        //}

        //if (leftResultValues.empty() || rightResultValues.empty()) {
        //    result.setResultTrue(false);
        //    return result;
        //}

        if (tempResultTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        //result.setFirstArg(leftArg, leftResultValues);
        //result.setSecondArg(rightArg, rightResultValues);
        result.setClauseResult(true, true, tempResultTable);
    }
    else {
        throw std::runtime_error("Unhandled left or right arg type in ParentHandler");
    }


    return result;


}