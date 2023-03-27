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

Result CallsHandler::evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    //std::string leftType = Utility::getReferenceType(leftArg);
    //std::string rightType = Utility::getReferenceType(rightArg);
    Result result;
    ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
    ReferenceType rightType = Utility::getEnumReferenceType(rightArg);
    switch (leftType)
    {
    case UNDERSCORE:
        switch (rightType)
        {
        case UNDERSCORE: {
            bool isCallsEmpty = isCallsEmptyFromPKB(isStar); 
            if (isCallsEmpty) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
        case QUOTED_IDENT: {
            std::set<std::string> callerSet = getCallsFromPKB(isStar, GET_CALLER, Utility::trim_double_quotes(rightArg));
            if (callerSet.empty()) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
                         //UNDERSCORE-Procedure
        default: {
            std::string synonDeType = synonymTable.find(rightArg)->second;
            std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
            // currSynonValues here are statement line numbers in string format.
            std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
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
            break;
        }
        }
        break;

    case QUOTED_IDENT:
        switch (rightType)
        {
        case UNDERSCORE: {
            std::set<string> calleeSet = getCallsFromPKB(isStar, GET_CALLEE, Utility::trim_double_quotes(leftArg));
            if (calleeSet.empty()) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
        case QUOTED_IDENT: {
            bool isCalls = getIsCallsFromPKB(isStar, Utility::trim_double_quotes(leftArg), Utility::trim_double_quotes(rightArg));
            if (!isCalls) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
                         //QUOTED_IDENT-Procedure
        default: {
            std::string synonDeType = synonymTable.find(rightArg)->second;
            resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
            std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
                bool isCalls = getIsCallsFromPKB(isStar, Utility::trim_double_quotes(leftArg), currSynonVal);
                if (isCalls) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
            if (resultSynonValues.empty()) {
                result.setResultTrue(false);
                return result;
            }
            result.setClauseResult(ResultTable(resultSynonValues, rightArg));
            break;
        }
        }
        break;
    default:
        switch (rightType)
        {
        case UNDERSCORE: {
            std::string synonDeType = synonymTable.find(leftArg)->second;

            std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
            // currSynonValues here are statement line numbers in string format.
            std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());

            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
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
            break;
        }
        case QUOTED_IDENT: {
            std::string synonDeType = synonymTable.find(leftArg)->second;
            //resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
            std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
            std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
            std::vector<std::string> resultSynonValues;

            for (const std::string& currSynonVal : currSynonValues) {
                bool isCalls = getIsCallsFromPKB(isStar, currSynonVal, Utility::trim_double_quotes(rightArg));
                if (isCalls) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
            if (resultSynonValues.empty()) {
                result.setResultTrue(false);
                return result;
            }
            result.setClauseResult(ResultTable(resultSynonValues, leftArg));
            break;
        }
                         //Procedure-Procedure
        default: {
            if (leftArg == rightArg) {
                result.setResultTrue(false);
                return result;
            }
            std::string leftDeType = synonymTable.find(leftArg)->second;
            std::string rightDeType = synonymTable.find(rightArg)->second;
            std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
            std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
            std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
            std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

            ResultTable initTable(currLeftValues, leftArg);
            initTable.combineTable(ResultTable(currRightValues, rightArg));
            int initTableSize = initTable.getColNum();

            ResultTable tempTable({ leftArg, rightArg });

            for (int i = 0; i < initTableSize; i++) {
                std::vector<std::string> tuple = initTable.getTuple(i);
                bool isLeftCallsRight = getIsCallsFromPKB(isStar, tuple[0], tuple[1]);
                if (isLeftCallsRight) {
                    tempTable.insertTuple({ tuple[0], tuple[1] });
                }
            }
            if (tempTable.isTableEmpty()) {
                result.setResultTrue(false);
                return result;
            }

            result.setClauseResult(tempTable);
            break;
        }
        }
        break;
    }
    return result;
    //// UNDERSCORE-UNDERSCORE
    //if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
    //    bool isCallsEmpty = isCallsEmptyFromPKB(isStar); //
    //    if (isCallsEmpty) {
    //        result.setResultTrue(false);
    //        return result;
    //    }     
    //}
    //// UNDERSCORE-QUOTED_IDENT
    //else if (leftType == Utility::UNDERSCORE && rightType == Utility::QUOTED_IDENT) {
    //    std::set<std::string> callerSet = getCallsFromPKB(isStar, GET_CALLER, Utility::trim_double_quotes(rightArg)); 
    //    if (callerSet.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }       
    //}
    //// UNDERSCORE-Procedure
    //else if (leftType == Utility::UNDERSCORE) {
    //    std::string synonDeType = synonymTable.find(rightArg)->second;      
    //    std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
    //    // currSynonValues here are statement line numbers in string format.
    //    std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        std::set<string> callerSet = getCallsFromPKB(isStar, GET_CALLER, currSynonVal);
    //        if (!callerSet.empty()) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    //}
    //// QUOTED_IDENT-UNDERSCORE
    //else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
    //    std::set<string> calleeSet = getCallsFromPKB(isStar, GET_CALLEE, Utility::trim_double_quotes(leftArg));
    //    if (calleeSet.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// QUOTED_IDENT-QUOTED_IDENT
    //else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
    //    bool isCalls = getIsCallsFromPKB(isStar, Utility::trim_double_quotes(leftArg), Utility::trim_double_quotes(rightArg));
    //    if (!isCalls) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// QUOTED_IDENT-Procedure
    //else if (leftType == Utility::QUOTED_IDENT) {
    //    std::string synonDeType = synonymTable.find(rightArg)->second;
    //    resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
    //    std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        bool isCalls = getIsCallsFromPKB(isStar, Utility::trim_double_quotes(leftArg), currSynonVal);
    //        if (isCalls) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    //}
    //// Procedure-UNDERSCORE
    //else if (rightType == Utility::UNDERSCORE) {
    //    std::string synonDeType = synonymTable.find(leftArg)->second;
    //   
    //    std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
    //    // currSynonValues here are statement line numbers in string format.
    //    std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());

    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        std::set<string> calleeSet = getCallsFromPKB(isStar, GET_CALLEE, currSynonVal);
    //        if (!calleeSet.empty()) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    //}
    //// Procedure-QUOTED_IDENT
    //else if (rightType == Utility::QUOTED_IDENT) {
    //    std::string synonDeType = synonymTable.find(leftArg)->second;
    //    //resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
    //    std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
    //    std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
    //    std::vector<std::string> resultSynonValues;

    //    for (const std::string& currSynonVal : currSynonValues) {
    //        bool isCalls = getIsCallsFromPKB(isStar, currSynonVal, Utility::trim_double_quotes(rightArg));
    //        if (isCalls) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    //}
    //// Procedure-Procedure
    //else {
    //    if (leftArg == rightArg) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    std::string leftDeType = synonymTable.find(leftArg)->second;
    //    std::string rightDeType = synonymTable.find(rightArg)->second;
    //    std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
    //    std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
    //    //resultTable.resultTableCheckAndAdd(leftArg, pkb, leftDeType);
    //    //resultTable.resultTableCheckAndAdd(rightArg, pkb, rightDeType);
    //    std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
    //    std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

    //    //std::vector<std::string> currLeftValues = resultTable.getSynValues(leftArg);
    //    //std::vector<std::string> currRightValues = resultTable.getSynValues(rightArg);
    //    ResultTable initTable(currLeftValues, leftArg);
    //    initTable.combineTable(ResultTable(currRightValues, rightArg));
    //    int initTableSize = initTable.getColNum();

    //    ResultTable tempTable({ leftArg, rightArg });

    //    for (int i = 0; i < initTableSize; i++) {
    //        std::vector<std::string> tuple = initTable.getTuple(i);
    //        bool isLeftCallsRight = getIsCallsFromPKB(isStar, tuple[0], tuple[1]);
    //        if (isLeftCallsRight) {
    //            tempTable.insertTuple({ tuple[0], tuple[1] });
    //        }
    //    }
    //    if (tempTable.isTableEmpty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }

    //    result.setClauseResult(tempTable);
    //}

    //return result;
}