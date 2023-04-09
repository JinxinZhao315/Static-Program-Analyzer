#include "qps/include/model/Query.h"
#include "pkb/include/PKB.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/ResultTable.h"
#include "SelectHandler.h"
#include "qps/include/evaluator/WithHandler.h"
#include "qps/include/evaluator/PatternHandler.h"
#include "qps/include/evaluator/SuchThatHandler.h"
#include "common/include/utils/Utility.h"
#include <numeric>
#include <string>
#include <set>
#include <unordered_map>
#ifndef SPA_PQLEVALUATOR_H
#define SPA_PQLEVALUATOR_H


class PQLEvaluator {
public:
    PQLEvaluator(PKB& pkb);
    std::set<std::string> evaluate(Query query);

private:
    PKB pkb;
    void evalClause(Clause* clause, bool& isEarlyExit, std::multimap<std::string, std::string> synonymTable, 
        ResultTable& resultTable, std::vector<std::string> synUsageSequence, int& currSynEvalPos);
};


#endif //SPA_PQLEVALUATOR_H
