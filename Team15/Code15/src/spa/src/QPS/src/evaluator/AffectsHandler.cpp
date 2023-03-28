#include "QPS/include/evaluator/AffectsHandler.h"

AffectsHandler::AffectsHandler(PKB& pkb) : ClauseHandler(pkb) {
}


std::set<int> AffectsHandler::getAffectsFromPKB(bool isStar, string type, string arg) {
    std::set<int> ret;
    if (!isStar) {
        if (type == GET_LEADER) {
            
            ret = pkb.getAffectsModifierStmtNums(stoi(arg));
        }
        else { //if (type == GET_FOLLOWER)
            
            ret = pkb.getAffectsUserStmtNums(stoi(arg));
            
        }
    }
    else {
        if (type == GET_LEADER) {
            ret = pkb.getAffectsStarModifierStmtNums(stoi(arg));
           
        }
        else { //  if (type == GET_FOLLOWER)
            
            ret = pkb.getAffectsStarUserStmtNums(stoi(arg));
        }
    }
    return ret;
}

bool AffectsHandler::getIsAffectsFromPKB(bool isStar, string leftArg, string rightArg) {
    bool ret;
    if (isStar) {
        ret = pkb.areInAffectsStarRelationship(stoi(leftArg), stoi(rightArg));
    }
    else {
        ret = pkb.areInAffectsRelationship(stoi(leftArg), stoi(rightArg));
    }
    return ret;
}

bool AffectsHandler::isAffectsEmptyFromPKB(bool isStar) {
    bool ret;
    if (isStar) {
        ret = pkb.isAffectsStarEmpty();
    }
    else {
        ret = pkb.isAffectsEmpty();
    }
    return ret;
}

Result AffectsHandler::evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    //std::string leftType = Utility::getReferenceType(leftArg);
    //std::string rightType = Utility::getReferenceType(rightArg);
    Result result;
    ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
    ReferenceType rightType = Utility::getEnumReferenceType(rightArg);
    switch (leftType)
    {
    case SYNONYM:
        switch (rightType)
        {
        case SYNONYM: {
            if (leftArg == rightArg) {
                result.setResultTrue(false);
                return result;
            }
            std::string leftDeType = synonymTable.find(leftArg)->second;
            std::string rightDeType = synonymTable.find(rightArg)->second;
            std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
            std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
            //convert the set to vector
            std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
            std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

            ResultTable initTable(currLeftValues, leftArg);
            initTable.combineTable(ResultTable(currRightValues, rightArg));
            int initTableSize = initTable.getColNum();

            ResultTable tempTable({ leftArg, rightArg });

            for (int i = 0; i < initTableSize; i++) {
                std::vector<std::string> tuple = initTable.getTuple(i);
                bool isLeftAffectsRight = getIsAffectsFromPKB(isStar, tuple[0], tuple[1]);
                if (isLeftAffectsRight) {
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
            
        case INTEGER: {
            std::string synonDeType = synonymTable.find(leftArg)->second;
            resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
            std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
                bool isAffects = getIsAffectsFromPKB(isStar, currSynonVal, rightArg);
                if (isAffects) {
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
            
        case UNDERSCORE: {
            std::string synonDeType = synonymTable.find(leftArg)->second;
            resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
            std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
                std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_FOLLOWER, currSynonVal);
                if (!affectsSet.empty()) {
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
           
        default:
            break;
        }
        break;
    case INTEGER:
        switch (rightType)
        {
        case SYNONYM: {
            std::string synonDeType = synonymTable.find(rightArg)->second;
            resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
            std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
                bool isAffects = getIsAffectsFromPKB(isStar, leftArg, currSynonVal);
                if (isAffects) {
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
            
        case INTEGER: {
            bool isAffects = getIsAffectsFromPKB(isStar, leftArg, rightArg);
            if (!isAffects) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
            
        case UNDERSCORE: {
            std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_FOLLOWER, leftArg);
            if (affectsSet.empty()) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
           
        default:
            break;
        }
        break;
    case UNDERSCORE:
        switch (rightType)
        {
        case SYNONYM: {
            std::string synonDeType = synonymTable.find(rightArg)->second;
            resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
            std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
            std::vector<std::string> resultSynonValues;
            for (const std::string& currSynonVal : currSynonValues) {
                std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_LEADER, currSynonVal);
                if (!affectsSet.empty()) {
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
           
        case INTEGER: {
            std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_LEADER, rightArg);
            if (affectsSet.empty()) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
           
        case UNDERSCORE: {
            bool isAffectsEmpty = isAffectsEmptyFromPKB(isStar); //
            if (isAffectsEmpty) {
                result.setResultTrue(false);
                return result;
            }
            break;
        }
        default:
            break;
        }
        break;
    default:
        break;
    }
    return result;
    //// UNDERSCORE-UNDERSCORE
    //if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
    //    bool isAffectsEmpty = isAffectsEmptyFromPKB(isStar); //
    //    if (isAffectsEmpty) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// UNDERSCORE-INTEGER
    //else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
    //    std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_LEADER, rightArg);
    //    if (affectsSet.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// UNDERSCORE-SYNONYM
    //else if (leftType == Utility::UNDERSCORE) {
    //    std::string synonDeType = synonymTable.find(rightArg)->second;
    //    resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
    //    std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_LEADER, currSynonVal);
    //        if (!affectsSet.empty()) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    //}
    //// INTEGER-UNDERSCORE
    //else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
    //    std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_FOLLOWER, leftArg);
    //    if (affectsSet.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// INTEGER-INTEGER
    //else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
    //    bool isAffects = getIsAffectsFromPKB(isStar, leftArg, rightArg);
    //    if (!isAffects) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //}
    //// INTEGER-SYNONYM
    //else if (leftType == Utility::INTEGER) {
    //    std::string synonDeType = synonymTable.find(rightArg)->second;
    //    resultTable.resultTableCheckAndAdd(rightArg, pkb, synonDeType);
    //    std::vector<std::string> currSynonValues = resultTable.getSynValues(rightArg);
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        bool isAffects = getIsAffectsFromPKB(isStar, leftArg, currSynonVal);
    //        if (isAffects) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, rightArg));
    //}
    //// SYNONYM-UNDERSCORE
    //else if (rightType == Utility::UNDERSCORE) {
    //    std::string synonDeType = synonymTable.find(leftArg)->second;
    //    resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
    //    std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        std::set<int> affectsSet = getAffectsFromPKB(isStar, GET_FOLLOWER, currSynonVal);
    //        if (!affectsSet.empty()) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    //}
    //// SYNONYM-INTEGER
    //else if (rightType == Utility::INTEGER) {
    //    std::string synonDeType = synonymTable.find(leftArg)->second;
    //    resultTable.resultTableCheckAndAdd(leftArg, pkb, synonDeType);
    //    std::vector<std::string> currSynonValues = resultTable.getSynValues(leftArg);
    //    std::vector<std::string> resultSynonValues;
    //    for (const std::string& currSynonVal : currSynonValues) {
    //        bool isAffects = getIsAffectsFromPKB(isStar, currSynonVal, rightArg);
    //        if (isAffects) {
    //            resultSynonValues.push_back(currSynonVal);
    //        }
    //    }
    //    if (resultSynonValues.empty()) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    //}
    //// SYNONYM-SYNONYM
    //else {
    //    if (leftArg == rightArg) {
    //        result.setResultTrue(false);
    //        return result;
    //    }
    //    std::string leftDeType = synonymTable.find(leftArg)->second;
    //    std::string rightDeType = synonymTable.find(rightArg)->second;
    //    std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
    //    std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
    //    //convert the set to vector
    //    std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
    //    std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());

    //    ResultTable initTable(currLeftValues, leftArg);
    //    initTable.combineTable(ResultTable(currRightValues, rightArg));
    //    int initTableSize = initTable.getColNum();

    //    ResultTable tempTable({ leftArg, rightArg });

    //    for (int i = 0; i < initTableSize; i++) {
    //        std::vector<std::string> tuple = initTable.getTuple(i);
    //        bool isLeftAffectsRight = getIsAffectsFromPKB(isStar, tuple[0], tuple[1]);
    //        if (isLeftAffectsRight) {
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