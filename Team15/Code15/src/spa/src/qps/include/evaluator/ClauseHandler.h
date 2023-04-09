#include "pkb/include/PKB.h"
#include "qps/include/model/ResultTable.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/SuchThatClause.h"
#include "qps/include/model/PatternClause.h"
#include "qps/include/model/WithClause.h"
#include "common/include/utils/Utility.h"


#ifndef SPA_CLAUSEHANDLER_H
#define SPA_CLAUSEHANDLER_H

 class ClauseHandler
{
public:    
    PKB pkb;
    explicit ClauseHandler(PKB &pkb);


    virtual Result evaluate(bool isStar, SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {return {};};
    virtual Result evaluate(SuchThatClause suchThatClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable, 
        int& synEvalPosition, std::vector<std::string>evalSynList) {return {};};
    virtual Result evaluate(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable, 
        int& synEvalPosition, std::vector<std::string>evalSynList) {return {};};
    virtual Result evaluate(WithClause withClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
        int& synEvalPosition, std::vector<std::string>evalSynList) {return {};};

    void removeUselessSyns(std::vector<std::string>synsToCheck, ResultTable& resultTable, std::vector<std::string>evalSynList, int& synEvalPosition);
 };

#endif // SPA_CLAUSEHANDLER_H
