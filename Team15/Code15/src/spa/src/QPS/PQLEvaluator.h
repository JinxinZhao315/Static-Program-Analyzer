//
// Created by Jinxin Zhao on 2/2/23.
//
#include "QPS/Query.h"
#include "PKB.h"
<<<<<<< HEAD:Team15/Code15/src/spa/src/PQLEvaluator.h
#include "relationship_handlers/Result.h"
#include "relationship_handlers/ResultTable.h"
#include "relationship_handlers/SelectHandler.h"
#include "relationship_handlers/FollowsHandler.h"
// TODO: repetitive declaration?
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/ParentHandler.h"
#include "relationship_handlers/ModifiesHandler.h"
=======
#include "QPS/relationship_handlers/Result.h"
#include "QPS/relationship_handlers/ResultTable.h"
#include "QPS/relationship_handlers/SelectHandler.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
>>>>>>> eac2749300d94599e06342a54ea04939e55d71cf:Team15/Code15/src/spa/src/QPS/PQLEvaluator.h
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
