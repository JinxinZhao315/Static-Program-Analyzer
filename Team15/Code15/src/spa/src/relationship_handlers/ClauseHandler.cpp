//
// Created by Jinxin Zhao on 3/2/23.
//

#include "ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}

void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {

    std::string synonymName;
    std::set<std::string> synonymSet;

    if (result.isLeftArgSynonym()) {
        synonymName = result.getLeftArgName();
        synonymSet = result.getLeftArgValue();
        combine(synonymName, synonymSet, resultTable);
    }
    if (result.isRightArgSynonym()) {
        synonymName = result.getRightArgName();
        synonymSet = result.getRightArgValue();
        combine(synonymName, synonymSet, resultTable);
    }
   
}
void ClauseHandler::combine(std::string synonymName, std::set<std::string>synonymSet, ResultTable& resultTable) {
    std::set<std::string> intersection;
    std::insert_iterator<std::set<std::string>> intersectIterate(intersection, intersection.begin());
    if (resultTable.isKeyPresent(synonymName)) {
        std::set<std::string> currSynonymValue = resultTable.getValueFromKey(synonymName);
        set_intersection(synonymSet.begin(), synonymSet.end(), currSynonymValue.begin(), currSynonymValue.end(), intersectIterate);
        resultTable.insertKeyValuePair(synonymName, intersection);
    }
    else {
        resultTable.insertKeyValuePair(synonymName, synonymSet);
    }
}

std::set<std::string> ClauseHandler::getResultFromPKB(PKB& pkb, std::string resultType) {
    std::set<std::string> temp;
    if (resultType == "constant") {
        //convertVecToSet(pkb.getConstants());
        return temp;
    }
    else if (resultType == "procedure") {
        //pkb.getProcedures();
        return temp;
    }
    else if (resultType == "variable") {
        //pkb.getVariables();
        return temp;
    }
    else {
        //pkb.getEntities(resultType);
        return temp;
    }
}

template <typename T>
std::set<T> ClauseHandler::convertVecToSet(std::vector<T> vec) {
    std::set<T> resultSet;
    for (T t : vec) {
        resultSet.insert(t);
    }
    return resultSet;
}

// This function can only be used to check and add statements
void ClauseHandler::resultTableCheckAndAdd(string arg, ResultTable& resultTable) {
    if (!resultTable.isKeyPresent(arg)) {
        std::set<int> allStmtIntSet; //pkb.getAllStmtNums()
        std::set<string> allStmtStrSet;
        for (int stmtNum: allStmtIntSet) {
            allStmtStrSet.insert(to_string(stmtNum));
        }
        resultTable.insertKeyValuePair(arg, allStmtStrSet);
    }
}