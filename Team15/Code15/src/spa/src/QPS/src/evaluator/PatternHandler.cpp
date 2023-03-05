
#include "QPS/include/evaluator/PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}


set<string> PatternHandler::findMatchingLineNums(set<vector<string>> allRHS, string substrToMatch) {
    set <string> ret;
    for (vector<string> rhsExpr : allRHS) {
        bool isMatch = findIsMatch(rhsExpr, substrToMatch);
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


bool PatternHandler::findIsMatch(vector<string> rhsTokensVec, string substrToMatch) {
    pair<bool, string> trimmedPair = trimPattern(substrToMatch);
    bool isPartialMatch = trimmedPair.first;
    vector<string> substrTokens = tokenise(trimmedPair.second);
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


    if (firstType == Utility::UNDERSCORE) {

        std::vector<std::string> patternSynonVals;

        if (secondType == Utility::UNDERSCORE) {

            // result maintains current values of patternSynon
            patternSynonVals = resultTable.getSynValues(patternSynon);

        } else if (secondType == Utility::UNDERSCORED_EXPR) {

            std::vector<std::string> patternSynonLineNums = resultTable.getSynValues(patternSynon);

            for (string lineNum : patternSynonLineNums) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromStmt(stoi(lineNum));
                set<string> matchingLines = findMatchingLineNums(allRHS, secondArg);
                if (!matchingLines.empty()) {
                    patternSynonVals.push_back(lineNum);

                }
            }
        }

        result.setClauseResult(true, false, ResultTable(patternSynonVals, patternSynon));

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

        } else if (secondType == Utility::UNDERSCORED_EXPR) {

            for (string currFirstVal: currFirstSynonValues) {
                set<vector<string>> matchingRHS = pkb.getAssignExprsFromVar(currFirstVal);
                set<string> matchingLines = findMatchingLineNums(matchingRHS, secondArg);
                if (!matchingLines.empty()) {
                    for (string lineStr : matchingLines) {
                        tempResultTable.insertTuple({lineStr, currFirstVal });

                    }
                }
            }
        }

        result.setClauseResult(true, true, tempResultTable);

    } else if (firstType == Utility::QUOTED_IDENT) {

        string firstArgTrimmed = trimPattern(firstArg).second;
        std::vector<std::string> patternSynonVals;


        if (secondType == Utility::UNDERSCORE) {

            set<int> lineNumSet = getPatternFromPkb(patternType, firstArgTrimmed);
            // If second arg is wildcard, get every assign/while/if from pkb whose LHS is firstArgTrimmed (a variable)
            for (int num : lineNumSet) {
                patternSynonVals.push_back(to_string(num));
            }

        } else if (secondType == Utility::UNDERSCORED_EXPR) {
            set<vector<string>> matchingRHS = pkb.getAssignExprsFromVar(firstArgTrimmed);
            set<string> matchingLines = findMatchingLineNums(matchingRHS, secondArg);
            for (string lineStr : matchingLines) {
                patternSynonVals.push_back(lineStr);
            }
        }

        result.setClauseResult(true, false, ResultTable(patternSynonVals, patternSynon));

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}



// Return a pair, where first element boolean = true if input is asking for partial match (e.g. _"x"_)
//, and false if input is aksing for full match (e.g. "x")
// Second element string is input trimmed of underscore and quotes
pair<bool,string> PatternHandler::trimPattern(string input) {
    std::string trimmed = input;

    // Trim underscore
    std::size_t firstUnderscore = trimmed.find_first_not_of(Utility::UNDERSCORE);
    bool isLeftUnderscore = false;
    bool isRightUnderscore = false;

    // trim left
    if (firstUnderscore != std::string::npos) {
        trimmed = trimmed.substr(firstUnderscore);
        isLeftUnderscore = true;
    }
    // trim right
    std::size_t lastUnderscore = trimmed.find_last_not_of(Utility::UNDERSCORE);
    if (lastUnderscore != std::string::npos) {
        trimmed = trimmed.substr(0, lastUnderscore + 1);
        isRightUnderscore = true;
    }

    // XOR of isLeftUnderscore and isRightUnderscore
    // This should never trigger if syntax checking works correctly
    if (!isLeftUnderscore != !isRightUnderscore) {
        throw PQLSyntaxError("PQL syntax error: Incorrect partial matching format in pattern clause");
    }

    // Under valid syntax, either isLeftUnderscore and isRightUnderscore are both false, or both true
    bool isPartialMatch = isLeftUnderscore && isRightUnderscore;

    trimmed = Utility::trim(trimmed, Utility::QUOTE);
    trimmed = Utility::trim(trimmed, Utility::WHITESPACES);

    return make_pair(isPartialMatch, trimmed);

}


