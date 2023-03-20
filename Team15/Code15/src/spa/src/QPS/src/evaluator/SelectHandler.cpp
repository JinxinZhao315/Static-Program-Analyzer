#include "QPS/include/evaluator/SelectHandler.h"

SelectHandler::SelectHandler(PKB& pkb) {
    this->pkb = pkb;
}

std::vector<Elem> SelectHandler::evalSelect(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable) {
    std::vector<Elem> synNameVec = selectClause.getSynNameVec();
    for (Elem elem : synNameVec) {
        if (elem.getSynName() != "BOOLEAN" || varTable.count("BOOLEAN") > 0) {
            std::string synType = varTable.find(elem.getSynName())->second;
            resultTable.resultTableCheckAndAdd(elem.getSynName(), pkb, synType);
        }
    }

    return synNameVec;
}