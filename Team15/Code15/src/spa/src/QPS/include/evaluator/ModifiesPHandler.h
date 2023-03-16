#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_MODIFIESPHANDLER_H
#define SPA_MODIFIESPHANDLER_H


class ModifiesPHandler : public ClauseHandler {
public:
    explicit ModifiesPHandler(PKB& pkb);
    Result evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable) override;
//    Result evalModifiesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
private:
    string GET_PARENT = "get_parent";
    string GET_CHILD = "get_child";
};


#endif 