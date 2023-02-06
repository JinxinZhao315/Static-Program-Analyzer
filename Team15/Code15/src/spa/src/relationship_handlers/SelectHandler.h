#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "SelectClause.h"
#include <string>
#include <unordered_map>
#include <map>
#include <set>

#pragma once

class SelectHandler : public ClauseHandler {

public:
    SelectHandler(PKB &pkb);
    std::string evalSelect(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable);

private:
    ResultTable resultTable;
};
