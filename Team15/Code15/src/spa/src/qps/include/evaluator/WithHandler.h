#include <map>
#include "qps/include/model/WithClause.h"
#include "qps/include/evaluator/ClauseHandler.h"
#include "./exceptions/PQLSemanticError.h"

#pragma once

class WithHandler: public ClauseHandler {
private:

public:
	explicit WithHandler(PKB& pkb);
	Result evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
		int& synEvalPosition, std::vector<std::string>evalSynList) override;
};