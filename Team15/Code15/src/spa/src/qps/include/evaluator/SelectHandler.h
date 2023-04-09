#include "qps/include/evaluator/ClauseHandler.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/ResultTable.h"
#include "qps/include/model/SelectClause.h"
#include <string>
#include <unordered_map>
#include <map>
#include <set>

#pragma once

class SelectHandler{

public:
    explicit SelectHandler(PKB &pkb);
    std::vector<Elem*> evaluate(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable);

private:
    PKB pkb;
};
