//
// Created by Jinxin Zhao on 2/2/23.
//
#include "Query.h"
#include "PKB.h"
#include "relationship_handlers/Result.h"
#include "relationship_handlers/SelectHandler.h"
#include "relationship_handlers/FollowsHandler.h"
#include "relationship_handlers/ResultTable.h"
#include <string>
#include <set>
#include <unordered_map>
#ifndef SPA_PQLEVALUATOR_H
#define SPA_PQLEVALUATOR_H


class PQLEvaluator {
public:
    PQLEvaluator(PKB& pkb);
    std::string evaluate(Query query);
    std::string parseSelectClause(SelectClause selectClause, std::multimap<std::string, std::string> varTable, PKB& pkb, ResultTable& resultTable);
    std::set<std::string> getResultFromPKB(PKB& pkb, std::string resultType);
    template <typename T>
    std::set<T> convertVecToSet(std::vector<T> vec);
private:
    PKB pkb;
};


#endif //SPA_PQLEVALUATOR_H
