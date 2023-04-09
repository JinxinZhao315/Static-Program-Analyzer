#include "qps/include/evaluator/ClauseHandler.h"

ClauseHandler::ClauseHandler(PKB& pkb) {
    this->pkb = pkb;
}

void ClauseHandler::removeUselessSyns(std::vector<std::string>synsToCheck, ResultTable& resultTable, std::vector<std::string>evalSynList, int& synEvalPosition) {
    for (int i = 0; i < synsToCheck.size(); i++) {
        if (!Utility::isSynUsedLater(evalSynList, synEvalPosition)) {
            resultTable.deleteSynonym(synsToCheck[i]);
        }
        synEvalPosition++;
    }
}