//
// Created by Jinxin Zhao on 2/2/23.
//
#include "QPS/Query.h"
#include "PKB.h"
<<<<<<< HEAD


=======
>>>>>>> d54c8469b4beb6a1aede62e86a93f7fa8618a823
#include "QPS/relationship_handlers/Result.h"
#include "QPS/relationship_handlers/ResultTable.h"
#include "QPS/relationship_handlers/SelectHandler.h"
#include "QPS/relationship_handlers/FollowsHandler.h"
<<<<<<< HEAD
#include "QPS/relationship_handlers/FollowsHandler.h"
=======
#include "QPS/relationship_handlers/ParentHandler.h"
#include "QPS/relationship_handlers/ModifiesHandler.h"
>>>>>>> d54c8469b4beb6a1aede62e86a93f7fa8618a823
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
