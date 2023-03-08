#include "QPS/include/evaluator/CallsHandler.h"

CallsHandler::CallsHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<std::string> CallsHandler::getCallsFromPKB(bool isStar, string type, string arg) {
    std::set<std::string> ret;
    if (!isStar) {
        if (type == GET_CALLER) {
            ret = pkb.getCallsCallerNames(arg);
        }
        else { //if (type == GET_CALLEE)
            ret = pkb.getCallsCalleeNames(arg);
        }
    }
    else {
        if (type == GET_CALLER) {
            ret = pkb.getCallsStarCallerNames(arg);
        }
        else { //  if (type == GET_CALLEE)
            ret = pkb.getCallsStarCalleeNames(arg);
        }
    }
    return ret;
}

bool CallsHandler::getIsCallsFromPKB(bool isStar, string leftArg, string rightArg) {
    bool ret;
    if (isStar) {
        ret = pkb.areInCallsStarRelationship(leftArg, rightArg);
    }
    else {
        ret = pkb.areInCallsRelationship(leftArg, rightArg);
    }
    return ret;
}

bool CallsHandler::isCallsEmptyFromPKB(bool isStar) {
    bool ret;
    if (isStar) {
        ret = pkb.isCallsStarEmpty();
    }
    else {
        ret = pkb.isCallsEmpty();
    }
    return ret;
}

Result CallsHandler::evalCalls(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    // UNDERSCORE-UNDERSCORE
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isCallsEmpty = isCallsEmptyFromPKB(isStar); //
        if (isCallsEmpty) {
            result.setResultTrue(false);
            return result;
        }     
    }
    // UNDERSCORE-QUOTED_IDENT
    else if (leftType == Utility::UNDERSCORE && rightType == Utility::QUOTED_IDENT) {
        std::set<std::string> callerSet = getCallsFromPKB(isStar, GET_CALLER, rightArg); 
        if (callerSet.empty()) {
            result.setResultTrue(false);
            return result;
        }       
    }
    // UNDERSCORE-Procedure
    else if (leftType == Utility::UNDERSCORE) {
        std::string synonDeType = synonymTable.find(rightArg)->second;
        resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
        std::vector<std::string> resultSynonValues;
        for (std::string currSynonVal : currSynonValues) {
            std::set<string> callerSet = getCallsFromPKB(isStar, GET_CALLER, currSynonVal);
            if (!callerSet.empty()) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    }
    // QUOTED_IDENT-UNDERSCORE
    else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
        std::set<string> calleeSet = getCallsFromPKB(isStar, GET_CALLEE, leftArg); 
        if (calleeSet.empty()) {
            result.setResultTrue(false);
            return result;
        }
    }
    // QUOTED_IDENT-QUOTED_IDENT
    else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
        bool isCalls = getIsCallsFromPKB(isStar, leftArg, rightArg);
        if (!isCalls) {
            result.setResultTrue(false);
            return result;
        }
    }
    // QUOTED_IDENT-Procedure
    else if (leftType == Utility::QUOTED_IDENT) {
        std::string synonDeType = synonymTable.find(rightArg)->second;
        resultTableCheckAndAdd(rightArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
        std::vector<std::string> resultSynonValues;
        for (std::string currSynonVal : currSynonValues) {
            bool isCalls = getIsCallsFromPKB(isStar, leftArg, currSynonVal);
            if (isCalls) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    }
    // Procedure-UNDERSCORE
    else if (rightType == Utility::UNDERSCORE) {
        std::string synonDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> resultSynonValues;
        for (std::string currSynonVal : currSynonValues) {
            std::set<string> calleeSet = getCallsFromPKB(isStar, GET_CALLEE, currSynonVal);
            if (!calleeSet.empty()) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    }
    // Procedure-QUOTED_IDENT
    else if (rightType == Utility::QUOTED_IDENT) {
        std::string synonDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, synonDeType);
        std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> resultSynonValues;
        for (std::string currSynonVal : currSynonValues) {
            bool isCalls = getIsCallsFromPKB(isStar, currSynonVal, rightArg);
            if (isCalls) {
                resultSynonValues.push_back(currSynonVal);
            }
        }
        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    }
    // Procedure-Procedure
    else {
        if (leftArg == rightArg) {
            result.setResultTrue(false);
            return result;
        }
        std::string leftDeType = synonymTable.find(leftArg)->second;
        std::string rightDeType = synonymTable.find(rightArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        resultTableCheckAndAdd(rightArg, resultTable, rightDeType);

        std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
        std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);

        ResultTable tempResultTable({ leftArg, rightArg });

        for (int i = 0; i < currLeftValues.size(); i++) {
            bool isLeftCallsRight = getIsCallsFromPKB(isStar, currLeftValues[i], currRightValues[i]); 
            if (isLeftCallsRight) {
                tempResultTable.insertTuple({ currLeftValues[i], currRightValues[i] });
            }
        }
        if (tempResultTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setClauseResult(tempResultTable);
    }

    return result;
}