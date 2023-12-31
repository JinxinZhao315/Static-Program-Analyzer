#include "qps/include/evaluator/ClauseHandler.h"
#include "qps/include/model/Result.h"
#include "qps/include/model/PatternClause.h"
#include "common/include/utils/StringOperations.h"
#include "common/include/utils/Utility.h"
#include <stack>
#include <cstddef>

#ifndef SPA_PATTERNHANDLER_H
#define SPA_PATTERNHANDLER_H


class PatternHandler:  public ClauseHandler {
public:
    explicit PatternHandler(PKB& pkb);
    Result evaluate(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
        int& synEvalPosition, std::vector<std::string>evalSynList) override;
private:
    string GET_FROM_VAR = "get_from_var";
    string GET_ALL = "get_all";
    vector<string> findMatchingLineNums(bool isPartialMatch, set<int> allStmtsWithLHS, const vector<string>& substrTokens);
    set<int> getLineNumsFromPkb(DesignEntity patternSynonType, const string& arg, const string& type);
    static bool findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec);
    static string trimExpr(string input);
    static vector<string> simplifiedTokenise(const string& input);
    static vector<string> simplifiedConvertToPostfix(vector<string> tokens);
    static bool isValidExprTerm(const string& token);
    static bool isValidStart(const string& token);
    static bool isValidEnd(const string& token);

};


#endif //SPA_PATTERNHANDLER_H
