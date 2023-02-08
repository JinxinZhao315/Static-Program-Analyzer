#include "QPS/Query.h"
#include "PKB.h"
#include "QPS/relationship_handlers/Result.h"
#include "QPS/relationship_handlers/ResultTable.h"
#include "QPS/relationship_handlers/SelectHandler.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
#include "QPS/relationship_handlers/PatternHandler.h"
#include <numeric>
#include <string>
#include <set>
#include <unordered_map>
#ifndef SPA_PQLEVALUATOR_H
#define SPA_PQLEVALUATOR_H


class PQLEvaluator {
public:
    PQLEvaluator(PKB& pkb);
    std::string evaluate(Query query);
private:
    PKB pkb;
};


#endif //SPA_PQLEVALUATOR_H
