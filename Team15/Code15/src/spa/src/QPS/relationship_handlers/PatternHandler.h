#include "ClauseHandler.h"
#include "Result.h"
#include "../PatternClause.h"

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
public:
    PatternHandler(PKB& pkb);
    Result evalPattern(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    set<string> findMatchingLines(set<pair<string, int>> allRHS, string strToMatch);

};


#endif //SPA_PATTERNHANDLER_H
