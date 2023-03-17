#include "pkb/include/PKB.h"
#include "QPS/include/model/ResultTable.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/SuchThatClause.h"
#include "QPS/include/model/PatternClause.h"
#include "QPS/include/model/WithClause.h"
#include "Utility.h"


#ifndef SPA_CLAUSEHANDLER_H
#define SPA_CLAUSEHANDLER_H

 class ClauseHandler
{
public:    
    PKB pkb;
    explicit ClauseHandler(PKB &pkb);
    void resultTableCheckAndAdd(string arg, ResultTable& resultTable, string DeType);
    std::set<std::string> getResultFromPKB(PKB& pkb, string DeType);

    virtual Result evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {return {};};
    virtual Result evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {return {};};
    virtual Result evaluate(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {return {};};
    virtual Result evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {return {};};
};

#endif // SPA_CLAUSEHANDLER_H
