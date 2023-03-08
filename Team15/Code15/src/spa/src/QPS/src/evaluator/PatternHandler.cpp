
#include "QPS/include/evaluator/PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}


set<string> PatternHandler::findMatchingLineNums(bool isPartialMatch, set<vector<string>> allRHS, string substrToMatch) {
    set <string> ret;
    for (vector<string> rhsExpr : allRHS) {
        bool isMatch = findIsMatch(isPartialMatch, rhsExpr, substrToMatch);
        if (isMatch) {
            set<int> lineNumSet = pkb.getAssignStmtsFromExpr(rhsExpr);
            for (int num : lineNumSet) {
                ret.insert(to_string(num));
            }
        }
    }
    return ret;

}


// This implementation is only for MS1 since there's no operators in pattern right arg
vector<string> PatternHandler::tokenise(string input) {
    vector<string> ret;
    ret.push_back(input);
    return ret;

}

// This implementation is only for MS1 since there's no operators in pattern right arg
vector<string> PatternHandler::convertToPostfix(vector<string> inputVec, int startIndex) {
    return inputVec;
}


bool PatternHandler::findIsMatch( bool isPartialMatch, vector<string> rhsTokensVec, string substrToMatch) {
    string trimmed = trimExpr(substrToMatch);
    vector<string> substrTokens = tokenise(trimmed);
    vector<string> substrPostfix = convertToPostfix(substrTokens, 0);
    if (!isPartialMatch) {
        return rhsTokensVec == substrPostfix;
    } else {
        return findIsPartialMatch(rhsTokensVec, substrPostfix);
    }
}

// Use sliding window to determine if substr is a subset of fullstr
bool PatternHandler::findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec) {
    size_t subStrSize = substrVec.size();
    size_t fullStrSize = fullstrVec.size();
    for (size_t windowStart = 0; windowStart <= fullStrSize - subStrSize; windowStart++)
    {
        for (size_t i = 0; i < subStrSize; i++)
        {
            if (substrVec[i] != fullstrVec[windowStart + i])
            {
                break;
            }
            if (i == subStrSize - 1) {
                return true;
            }

        }
    }

    return false;
}

set<int> PatternHandler::getPatternFromPkb(string patternSynonType, string arg) {
    set<int> lineNumSet;
    if (patternSynonType == "assign") {
        lineNumSet = pkb.getAssignStmtsFromVar(arg);
    } else if (patternSynonType == "while") {
        lineNumSet = pkb.getWhileStmtsFromVar(arg);
    } else { // if (patternSynonType == "if")
        lineNumSet = pkb.getIfStmtsFromVar(arg);
    }
    return lineNumSet;
}


Result PatternHandler::evalPattern(PatternClause patternClause, ResultTable &resultTable,
                                   std::multimap<std::string, std::string> &synonymTable) {

    string patternSynon = patternClause.getPatternSynonym();
    string firstArg = patternClause.getFirstArg();
    string secondArg = patternClause.getSecondArg();
    string firstType = Utility::getReferenceType(firstArg);
    string secondType = Utility::getReferenceType(secondArg);
    Result result;
    string patternType = synonymTable.find(patternSynon)->second;

    resultTableCheckAndAdd(patternSynon, resultTable, patternType);

    bool isPartialMatch;
    if (secondType == Utility::UNDERSCORED_EXPR) {
        isPartialMatch = true;
    } else  { // secondType = EXPR (full match) or UNDERSCORED (this bool is then useless)
        isPartialMatch = false;
    }


    if (firstType == Utility::UNDERSCORE) {

        std::vector<std::string> patternSynonVals;

        if (secondType == Utility::UNDERSCORE) {

            // result maintains current values of patternSynon
            patternSynonVals = resultTable.getSynValues(patternSynon);

        } else {
            std::vector<std::string> patternSynonLineNums = resultTable.getSynValues(patternSynon);

            for (string lineNum : patternSynonLineNums) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromStmt(stoi(lineNum));
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArg);
                if (!matchingLines.empty()) {
                    patternSynonVals.push_back(lineNum);

                }
            }
        }

        result.setClauseResult(ResultTable(patternSynonVals, patternSynon));

    } else if (firstType == Utility::SYNONYM) {

        string firstDeType = synonymTable.find(firstArg)->second;
        resultTableCheckAndAdd(firstArg, resultTable, firstDeType);
        std::vector<std::string> currFirstSynonValues = resultTable.getSynValues(firstArg);

        ResultTable tempResultTable({patternSynon, firstArg });


        if (secondType == Utility::UNDERSCORE) {

            for (string currFirstVal: currFirstSynonValues) {
                    set<int> lineNumSet = getPatternFromPkb(patternType, currFirstVal);
                    // If second arg is wildcard, get every assign/while/if from pkb whose LHS is currFirstVal ( a variable)
                    for (int num : lineNumSet) { // Each num is a possible value of pattern synon
                        string numStr = to_string(num);
                        tempResultTable.insertTuple({numStr, currFirstVal});
                    }
            }

        } else {

            for (string currFirstVal: currFirstSynonValues) {
                set<vector<string>> matchingRHS = pkb.getAssignExprsFromVar(currFirstVal);
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, matchingRHS, secondArg);
                if (!matchingLines.empty()) {
                    for (string lineStr : matchingLines) {
                        tempResultTable.insertTuple({lineStr, currFirstVal });

                    }
                }
            }
        }

        result.setClauseResult(tempResultTable);

    } else if (firstType == Utility::QUOTED_IDENT) {

        string firstArgTrimmed = trimExpr(firstArg);
        std::vector<std::string> patternSynonVals;


        if (secondType == Utility::UNDERSCORE) {

            set<int> lineNumSet = getPatternFromPkb(patternType, firstArgTrimmed);
            // If second arg is wildcard, get every assign/while/if from pkb whose LHS is firstArgTrimmed (a variable)
            for (int num : lineNumSet) {
                patternSynonVals.push_back(to_string(num));
            }

        } else {
            set<vector<string>> matchingRHS = pkb.getAssignExprsFromVar(firstArgTrimmed);
            set<string> matchingLines = findMatchingLineNums(isPartialMatch, matchingRHS, secondArg);
            for (string lineStr : matchingLines) {
                patternSynonVals.push_back(lineStr);
            }
        }

        result.setClauseResult(ResultTable(patternSynonVals, patternSynon));

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}



std::string PatternHandler::trimExpr(string input) {
    std::string trimmed = input;
    trimmed = Utility::trim(trimmed, Utility::UNDERSCORE);
    trimmed = Utility::trim(trimmed, Utility::QUOTE);
    trimmed = Utility::trim(trimmed, Utility::WHITESPACES);
    return trimmed;
}


