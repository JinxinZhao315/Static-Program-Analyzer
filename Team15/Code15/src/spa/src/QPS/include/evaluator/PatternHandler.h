#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/PatternClause.h"
#include "common/include/utils/StringOperations.h"
#include "Utility.h"
#include <stack>
#include "stddef.h"

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
private:
    string GET_FROM_VAR = "get_from_var";
    string GET_ALL = "get_all";
public:
    PatternHandler(PKB& pkb);
    Result evalPattern(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    set<string> findMatchingLineNums(bool isPartialMatch, set<vector<string>> allRHS, string substrToMatch);
    bool findIsMatch(bool isPartialMatch, vector<string> rhsTokensVec, string substrToMatch);
    bool findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec);
    vector<string> getStmtsFromPkb(string patternSynonType, string arg, string type);
    string trimExpr(string input);
    vector<string> simplifiedTokenise(string input);
    vector<string> simplifiedConvertToPostfix(vector<string> tokens);
    bool isValidExprTerm(string token);
};


#endif //SPA_PATTERNHANDLER_H
