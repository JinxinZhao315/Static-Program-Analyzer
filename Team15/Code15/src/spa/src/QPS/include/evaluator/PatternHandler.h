#include "QPS/include/evaluator/ClauseHandler.h"
#include "QPS/include/model/Result.h"
#include "QPS/include/model/PatternClause.h"
#include "common/include/utils/StringOperations.h"
#include "Utility.h"
#include <stack>
#include <cstddef>

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
private:
    string GET_FROM_VAR = "get_from_var";
    string GET_ALL = "get_all";
public:
    explicit PatternHandler(PKB& pkb);
    Result evalPattern(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable);
    set<string> findMatchingLineNums(bool isPartialMatch, const set<vector<string>>& allRHS, const vector<string>& substrTokens);
    vector<string> getStmtsFromPkb(const string& patternSynonType, const string& arg, const string& type);

    static bool findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec);
    static string trimExpr(string input);
    static vector<string> simplifiedTokenise(const string& input);
    static vector<string> simplifiedConvertToPostfix(vector<string> tokens);
    static bool isValidExprTerm(const string& token);
};


#endif //SPA_PATTERNHANDLER_H
