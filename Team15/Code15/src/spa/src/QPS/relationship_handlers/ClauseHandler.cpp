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
        Tokens::Keyword DeToken;
        if (DeType == "read") {
            DeToken = Tokens::Keyword::READ;
        } else if (DeType == "print") {
            DeToken = Tokens::Keyword::PRINT;
        } else if (DeType == "assign") {
            DeToken = Tokens::Keyword::ASSIGN;
        } else if (DeType == "call") {
            DeToken = Tokens::Keyword::CALL;
        } else if (DeType == "while") {
            DeToken = Tokens::Keyword::WHILE;
        } else if (DeType == "if") {
            DeToken = Tokens::Keyword::IF;
        } else {
            throw runtime_error("unsupported DeType in ClauseHandler");
        }

        std::set<int> allStmtIntSet = pkb.getAllStmtNumsByType(DeToken);
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