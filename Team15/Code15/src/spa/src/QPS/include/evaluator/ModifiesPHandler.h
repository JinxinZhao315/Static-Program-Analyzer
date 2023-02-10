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
    ModifiesPHandler(PKB& pkb);
    Result evalModifiesP(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    std::set<int> getModifiesPFromPKB(bool isStar, string type, string arg);
    bool getIsModifiesPFromPKB(bool isStar, string leftArg, string rightArg);
private:
    //todo ???
    string GET_PARENT = "get_parent";
    string GET_CHILD = "get_child";
};


#endif 