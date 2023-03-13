#include <map>
#include "QPS/include/model/WithClause.h"
#include "QPS/include/evaluator/ClauseHandler.h"

#pragma once

class WithHandler {
private:

public:
	WithHandler(PKB& pkb);
	Result evalWith(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
};