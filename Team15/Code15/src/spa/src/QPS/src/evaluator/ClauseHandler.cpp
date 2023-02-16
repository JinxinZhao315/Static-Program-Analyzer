#include "QPS/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}


void ClauseHandler::combineResult(ResultTable& resultTable, Result& result) {

    std::string synonymName;
    std::set<std::string> synonymSet;

    if (result.isFirstArgSynonym()) {
        synonymName = result.getFirstArgName();
        synonymSet = result.getFirstArgValue();
        combine(synonymName, synonymSet, resultTable);
    }
    if (result.isSecondArgSynonym()) {
        synonymName = result.getSecondArgName();
        synonymSet = result.getSecondArgValue();
        combine(synonymName, synonymSet, resultTable);
    }
   
}

void ClauseHandler::combine(std::string synonymName, std::set<std::string>& synonymSet, ResultTable& resultTable) {
    std::set<std::string> intersection;
    std::insert_iterator<std::set<std::string>> intersectIterate(intersection, intersection.begin());
    if (resultTable.isKeyPresent(synonymName)) {
       
        std::set<std::string> currSynonymValue = resultTable.getValueFromKey(synonymName);
        set_intersection(synonymSet.begin(), synonymSet.end(), currSynonymValue.begin(), currSynonymValue.end(), intersectIterate);
        resultTable.deleteKeyValuePair(synonymName);
        resultTable.insertKeyValuePair(synonymName, intersection);      
    }
    else {
        resultTable.insertKeyValuePair(synonymName, synonymSet);
    }
}

std::set<std::string> ClauseHandler::getResultFromPKB(PKB& pkb, string DeType) {
    std::set<std::string> ret;
    if (DeType == "constant") {
        ret = pkb.getAllConstVals();
    }
    else if (DeType == "procedure") {
        ret = pkb.getAllProcNames();
    }
    else if (DeType == "variable") {
        ret = pkb.getAllVarNames();
    }
    else if (DeType == "stmt") {
        std::set<int> allStmtIntSet = pkb.getAllStmtNums();
        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    } else  {
        std::set<int> allStmtIntSet = pkb.getAllStmtNumsByType(DeType);
        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    }
    return ret;
}

//template <typename T>
//std::set<T> ClauseHandler::convertVecToSet(std::vector<T> vec) {
//    std::set<T> resultSet;
//    for (T t : vec) {
//        resultSet.insert(t);
//    }
//    return resultSet;
//}

void ClauseHandler::resultTableCheckAndAdd(string arg, ResultTable& resultTable, string DeType) {
    if (!resultTable.isKeyPresent(arg)) {
        std::set<string> allStmtStrSet = getResultFromPKB(pkb, DeType);
        resultTable.insertKeyValuePair(arg, allStmtStrSet);
    }
}