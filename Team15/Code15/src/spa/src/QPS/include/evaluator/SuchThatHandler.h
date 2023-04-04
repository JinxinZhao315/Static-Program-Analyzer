#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/SuchThatClause.h"
#include <map>
#include <string>
#include <set>
#ifndef SPA_SUCHTHATHANDLER_H
#define SPA_SUCHTHATHANDLER_H


class SuchThatHandler : public ClauseHandler{
public:
    explicit SuchThatHandler(PKB& pkb);
    Result evaluate(Relationship relationship, SuchThatClause suchThatClause, 
        ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
        int& synEvalPosition, std::vector<std::string>evalSynList);

private:
    string GET_LEADER = "get_leader";
    string GET_FOLLOWER = "get_follower";
    bool getIsRelationshipSetEmpty(Relationship relationship, string type, string arg);
    bool getIsInRelationship(Relationship relationship, string leftArg, string rightArg);
    bool getIsPkbEmpty(Relationship relationship);
    std::set<std::string> getRelationshipSet(Relationship relationship, string type, string arg);
    void clearPkbTable(Relationship relatiionship);
};


#endif //SPA_SUCHTHATHANDLER_H
