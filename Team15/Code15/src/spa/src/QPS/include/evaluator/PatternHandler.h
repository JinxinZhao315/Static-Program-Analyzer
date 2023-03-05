#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "Utility.h"
#include "QPS/include/model/PatternClause.h"
#include <stack>
#include "stddef.h"

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
public:
    PatternHandler(PKB& pkb);
    Result evalPattern(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    set<string> findMatchingLineNums(set<vector<string>> allRHS, string substrToMatch);
    bool findIsMatch(vector<string> rhsTokensVec, string substrToMatch);
    bool findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec);
    set<int> getPatternFromPkb(string patternSynonType, string arg);
    pair<bool,string> trimPattern(string input);

    // TODO: These functions should be in common file
    vector<string>  convertToPostfix(vector<string> input, int startIndex);
    vector<string> tokenise(string input); // Need the same function as in SP but without the "extract" line

};


#endif //SPA_PATTERNHANDLER_H
