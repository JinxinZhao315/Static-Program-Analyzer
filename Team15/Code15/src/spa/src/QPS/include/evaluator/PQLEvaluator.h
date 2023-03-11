#include "QPS/include/model/Query.h"
#include "pkb/include/PKB.h"

#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "SelectHandler.h"
#include "QPS/include/evaluator/FollowsHandler.h"
#include "QPS/include/evaluator/ParentHandler.h"
#include "QPS/include/evaluator/ModifiesPHandler.h"
#include "QPS/include/evaluator/ModifiesSHandler.h"
#include "QPS/include/evaluator/PatternHandler.h"
#include "QPS/include/evaluator/UsesSHandler.h"
#include "QPS/include/evaluator/UsesPHandler.h"
#include "QPS/include/evaluator/CallsHandler.h"
#include "QPS/include/evaluator/NextHandler.h"
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
private:
    PKB pkb;
};


#endif //SPA_PQLEVALUATOR_H
