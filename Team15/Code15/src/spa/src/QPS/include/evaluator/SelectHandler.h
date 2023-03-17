#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SelectClause.h"
#include <string>
#include <unordered_map>
#include <map>
#include <set>

#pragma once

class SelectHandler{

public:
    explicit SelectHandler(PKB &pkb);
    std::vector<Elem> evalSelect(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable);

private:
    PKB pkb;
};
