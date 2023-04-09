#include "qps/include/evaluator/SelectHandler.h"

SelectHandler::SelectHandler(PKB& pkb) {
    this->pkb = pkb;
}

std::vector<Elem*> SelectHandler::evaluate(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable) {
    std::vector<Elem*> synNameVec = selectClause.getSelectedElements();
    for (Elem* elem : synNameVec) {
        if (elem->getSynName() != Utility::boolean || varTable.count(Utility::boolean) > 0) {
            std::string synType = varTable.find(elem->getSynName())->second;
            resultTable.resultTableCheckAndAdd(elem->getSynName(), pkb, synType);
        }
    }

    return synNameVec;
}