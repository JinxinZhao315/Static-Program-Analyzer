//
// Created by Qin Guorui on Feb 7.
//

#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "../SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_MODIFIESRHANDLER_H
#define SPA_MODIFIESRHANDLER_H


class ModifiesHandler : public ClauseHandler {
public:
    ModifiesHandler(PKB& pkb);
    Result evalModifies(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    std::set<int> getModifiesFromPKB(bool isStar, string type, string arg);
    bool getIsModifiesFromPKB(bool isStar, string leftArg, string rightArg);
private:
    //todo ???
    string GET_PARENT = "get_parent";
    string GET_CHILD = "get_child";
};


#endif 