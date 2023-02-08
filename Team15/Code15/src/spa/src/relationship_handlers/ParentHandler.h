//
// Created by Qin Guorui on Feb 7.
//

#include "ClauseHandler.h"
#include "Result.h"
#include "ResultTable.h"
#include "SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_PARENTSARHANDLER_H
#define SPA_PARENTSARHANDLER_H


class ParentHandler : public ClauseHandler {
public:
    ParentHandler(PKB& pkb);
    Result evalParentStar(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& varTable);
    std::set<int> getParentFromPKB(bool isStar, string type, string arg);
    bool getIsParentFromPKB(bool isStar, string leftArg, string rightArg);
private:
    string GET_PARENT = "get_parent";
    string GET_CHILD = "get_child";
};


#endif //SPA_PARENTSARHANDLER_H