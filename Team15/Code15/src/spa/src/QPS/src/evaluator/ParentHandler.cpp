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

Result ParentHandler::evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
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
        string synonDeType = synonymTable.find(leftArg)->second;
        /*resultTable.resultTableCheckAndAdd(leftArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);*/
        std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (const auto& currSynonVal : currSynonValues) {
                std::set<int> childSet = getParentFromPKB(isStar, GET_CHILD, currSynonVal); //=pkb.getFollowsStarFollowerNums(stoi(currSynonVal))
                if (!childSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (rightType == Utility::INTEGER) {
            for (const auto& currSynonVal : currSynonValues) {
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
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));

        // Wilcard/Int - Synon
    }
    else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string synonDeType = synonymTable.find(rightArg)->second;
        /*resultTable.resultTableCheckAndAdd(rightArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);*/
        std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (const auto& currSynonVal : currSynonValues) {
                std::set<int> parentSet = getParentFromPKB(isStar, GET_PARENT, currSynonVal); //=pkb.getFollowsStarLeaderNums(stoi(currSynonVal))
                if (!parentSet.empty()) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (leftType == Utility::INTEGER) {
            for (const auto& currSynonVal : currSynonValues) {
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
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));

        // Synon - Synon
    }
    else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        if (leftArg == rightArg) {
            result.setResultTrue(false);
            return result;
        }
        string leftDeType = synonymTable.find(leftArg)->second;
        string rightDeType = synonymTable.find(rightArg)->second;
        /*resultTable.resultTableCheckAndAdd(leftArg, pkb,  leftDeType);
        resultTable.resultTableCheckAndAdd(rightArg, pkb,  rightDeType);*/
        std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
        std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
        //convert the set to vector
        std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
        std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

        ResultTable initTable(currLeftValues, leftArg);
        initTable.combineTable(ResultTable(currRightValues, rightArg));
        int initTableSize = initTable.getColNum();

        //std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
        //std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);
        ResultTable tempTable({ leftArg, rightArg });

        for (int i = 0; i < initTableSize; i++) {
            std::vector<std::string> tuple = initTable.getTuple(i);
            bool isRightParentStarLeft = getIsParentFromPKB(isStar, tuple[0], tuple[1]); //=pkb.areInFollowsStarRelationship(currLeftVal, currRightVal)
            if (isRightParentStarLeft) {
                tempTable.insertTuple({ tuple[0], tuple[1] });
            }
        }

        if (tempTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(tempTable);
    }
    else {
        throw std::runtime_error("Unhandled left or right arg type in ParentHandler");
    }


    return result;


}