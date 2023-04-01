#include "QPS/include/evaluator/NextHandler.h"

NextHandler::NextHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> NextHandler::getNextFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_LEADER) {
            ret = pkb.getPreviousStmtNums(stoi(arg));
        }
        else { //if (type == GET_FOLLOWER)
            ret = pkb.getNextStmtNums(stoi(arg));
        }
    }
    else {
        if (type == GET_LEADER) {
            ret = pkb.getStarPreviousStmtNums(stoi(arg));
        }
        else { //  if (type == GET_FOLLOWER)
            ret = pkb.getStarNextStmtNums(stoi(arg));
        }
    }
    return ret;
}

bool NextHandler::getIsNextFromPKB(bool isStar, string leftArg, string rightArg) {
    bool ret;
    if (isStar) {
        ret = pkb.areInNextStarRelationship(stoi(leftArg), stoi(rightArg));
    }
    else {
        ret = pkb.areInNextRelationship(stoi(leftArg), stoi(rightArg));
    }
    return ret;
}

bool NextHandler::isNextEmptyFromPKB(bool isStar) {
    bool ret;
    if (isStar) {
        ret = pkb.isNextStarEmpty();
    }
    else {
        ret = pkb.isNextEmpty();
    }
    return ret;
}

Result NextHandler::evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    // UNDERSCORE-UNDERSCORE
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isNextEmpty = isNextEmptyFromPKB(isStar); //
        if (isNextEmpty) {
            result.setResultTrue(false);
            return result;
        }     
    }
    // UNDERSCORE-INTEGER
    else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
        std::set<int> nextSet = getNextFromPKB(isStar, GET_LEADER, rightArg); 
        if (nextSet.empty()) {
            result.setResultTrue(false);
            return result;
        }       
    }
    // UNDERSCORE-SYNONYM
    else if (leftType == Utility::UNDERSCORE) {
        std::string synonDeType = synonymTable.find(rightArg)->second;
        resultTable.resultTableCheckAndAdd(rightArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
        std::vector<std::string> resultSynonValues;
        for (const std::string& currSynonVal : currSynonValues) {
            std::set<int> nextSet = getNextFromPKB(isStar, GET_LEADER, currSynonVal);
            if (!nextSet.empty()) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    }
    // INTEGER-UNDERSCORE
    else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        std::set<int> nextSet = getNextFromPKB(isStar, GET_FOLLOWER, leftArg);
        if (nextSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
    }
    // INTEGER-INTEGER
    else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isNext = getIsNextFromPKB(isStar, leftArg, rightArg);
        if (!isNext) {
            result.setResultTrue(false);
            return result;
        }
    }
    // INTEGER-SYNONYM
    else if (leftType == Utility::INTEGER) {
        std::string synonDeType = synonymTable.find(rightArg)->second;
        resultTable.resultTableCheckAndAdd(rightArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
        std::vector<std::string> resultSynonValues;
        for (const std::string& currSynonVal : currSynonValues) {
            bool isNext = getIsNextFromPKB(isStar, leftArg, currSynonVal);
            if (isNext) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    }
    // SYNONYM-UNDERSCORE
    else if (rightType == Utility::UNDERSCORE) {
        std::string synonDeType = synonymTable.find(leftArg)->second;
        resultTable.resultTableCheckAndAdd(leftArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> resultSynonValues;
        for (const std::string& currSynonVal : currSynonValues) {
            std::set<int> nextSet = getNextFromPKB(isStar, GET_FOLLOWER, currSynonVal);
            if (!nextSet.empty()) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    }
    // SYNONYM-INTEGER
    else if (rightType == Utility::INTEGER) {
        std::string synonDeType = synonymTable.find(leftArg)->second;
        resultTable.resultTableCheckAndAdd(leftArg, pkb,  synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> resultSynonValues;
        for (const std::string& currSynonVal : currSynonValues) {
            bool isNext = getIsNextFromPKB(isStar, currSynonVal, rightArg);
            if (isNext) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    }
    // SYNONYM-SYNONYM
    else {
        //if (leftArg == rightArg) {
        //    result.setResultTrue(false);
        //    return result;
        //}
        std::string leftDeType = synonymTable.find(leftArg)->second;
        std::string rightDeType = synonymTable.find(rightArg)->second;
        /*resultTable.resultTableCheckAndAdd(leftArg, pkb,  leftDeType);
        resultTable.resultTableCheckAndAdd(rightArg, pkb,  rightDeType);*/
        std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
        std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
        //convert the set to vector
        std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
        std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());


        //std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
        //std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);

        ResultTable initTable(currLeftValues, leftArg);
        initTable.combineTable(ResultTable(currRightValues, rightArg));
        int initTableSize = initTable.getColNum();
        //in case leftArg == rightArg
        vector<std::string> argVec;
        if (leftArg == rightArg) {
            argVec = std::vector<std::string>({ leftArg });
        }
        else {
            argVec = std::vector<std::string>({ leftArg, rightArg });
        }

        ResultTable tempTable(argVec);

        for (int i = 0; i < initTableSize; i++) {
            std::vector<std::string> tuple = initTable.getTuple(i);
            std::string leftArgVal = tuple[0];
            std::string rightArgVal = leftArg == rightArg ? tuple[0] : tuple[1];

            bool isLeftNextRight = getIsNextFromPKB(isStar, leftArgVal, rightArgVal);
            if (isLeftNextRight) {
                tempTable.insertTuple(tuple);
            }
        }
        if (tempTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setClauseResult(tempTable);
    }
    return result;
}