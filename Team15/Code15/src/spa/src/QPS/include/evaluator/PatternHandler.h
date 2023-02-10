#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "Utility.h"
#include "QPS/include/model/PatternClause.h"

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
public:
    PatternHandler(PKB& pkb);
    Result evalPattern(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    set<string> findMatchingLineNums(set<pair<string, int>> allRHS, string substrToMatch);
    bool findIsMatch(string fullStr, string substrToMatch);
    pair<bool,string> trimUnderscoreQuotes(string input);
    string convertToPostfix(string input);
};


#endif //SPA_PATTERNHANDLER_H
