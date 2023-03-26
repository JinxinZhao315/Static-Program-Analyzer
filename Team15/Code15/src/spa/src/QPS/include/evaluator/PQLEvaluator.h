#include "QPS/include/model/Query.h"
#include "pkb/include/PKB.h"

#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "SelectHandler.h"
#include "QPS/include/evaluator/WithHandler.h"
#include "QPS/include/evaluator/PatternHandler.h"
#include "QPS/include/evaluator/SuchThatHandler.h"

#include "QPS/include/evaluator/ModifiesPHandler.h"
#include "QPS/include/evaluator/ModifiesSHandler.h"
#include "QPS/include/evaluator/UsesSHandler.h"
#include "QPS/include/evaluator/UsesPHandler.h"

#include "Utility.h"
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
    Result getSuchThatResult(SuchThatClause suchThatCl, const string& relationship, ResultTable resultTable, std::multimap<std::string, std::string> synonymTable);
private:
    PKB pkb;
    // helper function
    bool isArgUsedLater(std::vector<std::string> selectedSyn, std::vector<std::string> argList, int currArgPos);
};


#endif //SPA_PQLEVALUATOR_H
