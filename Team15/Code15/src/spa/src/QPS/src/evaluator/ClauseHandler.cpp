#include "QPS/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
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
    else {
        std::set<int> allStmtIntSet;

        if (DeType == "stmt") {
           allStmtIntSet = pkb.getAllStmtNums();
        } else if (DeType == "assign") {
            allStmtIntSet = pkb.getAllStmtNumsByType("=");
        } else {
            allStmtIntSet = pkb.getAllStmtNumsByType(DeType);
        }

        for (int stmtNum: allStmtIntSet) {
            ret.insert(to_string(stmtNum));
        }
    }
    return ret;
}

void ClauseHandler::resultTableCheckAndAdd(string synName, ResultTable& resultTable, string DeType) {
    if (!resultTable.isSynExist(synName)) {
        Result result;

        std::set<string> synValuesStrSet = getResultFromPKB(pkb, DeType);
        std::vector<string> synValuesStrVector(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::vector<std::string>> tempResult = { synValuesStrVector };
        std::vector<string> synList = { synName };
        ResultTable tempResultTable = ResultTable(tempResult, synList);
        resultTable.combineTable(tempResultTable);

    }
}

