#include <map>
#include "QPS/include/model/WithClause.h"
#include "QPS/include/evaluator/ClauseHandler.h"

#pragma once

class WithHandler: public ClauseHandler {
private:

public:
	explicit WithHandler(PKB& pkb);
	Result evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) override;
};