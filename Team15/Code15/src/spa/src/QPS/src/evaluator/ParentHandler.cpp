#include "QPS/include/evaluator/ParentHandler.h"

ParentHandler::ParentHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> ParentHandler::getParentFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_PARENT) {
            int parent = pkb.getParentParentNum(stoi(arg)); //
            if (parent != NULL) {
                ret.insert(parent);
            }
        }
        else { //if (type == GET_CHILD)
            int child = pkb.getParentChildNum(stoi(arg));//
            if (child != NULL) {
                ret.insert(child);
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
        //std::unordered_map<std::string, SynonymLinkageMap> parentSynonVals;

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
        for (const auto& elem : childSet) {
            std::cout << elem << " ";
        }
    
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
        std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);

        std::set<string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (string currSynonVal : currSynonValues) {
                std::set<int> childSet = getParentFromPKB(isStar, GET_CHILD, currSynonVal); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!childSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        else if (rightType == Utility::INTEGER) {
            for (string currSynonVal : currSynonValues) {
                bool isRightParentStarLeft = getIsParentFromPKB(isStar, currSynonVal, rightArg); //=pkb.areInFollowsStarRelationship(currSynonVal, rightArg)
                if (isRightParentStarLeft) {
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
    }
    else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string synonDeType = varTable.find(rightArg)->second;
        resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
        std::set<string> currSynonValues = resultTable.getValueFromKey(rightArg);
        std::set<string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (string currSynonVal : currSynonValues) {
                std::set<int> parentSet = getParentFromPKB(isStar, GET_PARENT, currSynonVal); //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!parentSet.empty()) {
                    resultSynonValues.insert(currSynonVal);
                }
            }
        }
        else if (leftType == Utility::INTEGER) {
            for (string currSynonVal : currSynonValues) {
                bool isRightParentStarLeft = getIsParentFromPKB(isStar, leftArg, currSynonVal); //=pkb.areInFollowsStarRelationship(leftArg, currSynonVal)
                if (isRightParentStarLeft) {
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
    }
    else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string leftDeType = varTable.find(leftArg)->second;
        string rightDeType = varTable.find(rightArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        resultTableCheckAndAdd(rightArg, resultTable, rightDeType);
        std::set<string> currLeftValues = resultTable.getValueFromKey(leftArg);
        std::set<string> currRightValues = resultTable.getValueFromKey(rightArg);

        std::set<string> leftResultValues;
        std::set<string> rightResultValues;

        for (string currLeftVal : currLeftValues) {
            for (string currRightVal : currRightValues) {
                bool isRightParentStarLeft = getIsParentFromPKB(isStar, currLeftVal, currRightVal); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
                if (isRightParentStarLeft) {
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
    }
    else {
        throw std::runtime_error("Unhandled left or right arg type in ParentHandler");
    }


    return result;


}