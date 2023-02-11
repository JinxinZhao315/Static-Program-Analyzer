
#include "QPS/include/evaluator/PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}


set<string> PatternHandler::findMatchingLineNums(set<vector<string>> allRHS, string substrToMatch) {
    set <string> ret;
    for (vector<string> rhsPostfix : allRHS) {
        bool isMatch = findIsMatch(rhsPostfix, substrToMatch);
        if (isMatch) {
            set<int> lineNumSet = pkb.getPatternStmtsFromPostfix(rhsPostfix);
            for (int num : lineNumSet) {
                ret.insert(to_string(num));
            }
        }
    }
    return ret;

}

vector<string> PatternHandler::tokenise(string input) {}
vector<string> PatternHandler::convertToPostfix(vector<string> input, int startIndex) {}


bool PatternHandler::findIsMatch(vector<string> rhsTokensVec, string substrToMatch) {
    pair<bool, string> trimmedPair = trimUnderscoreQuotes(substrToMatch);
    bool isPartialMatch = trimmedPair.first;
    vector<string> substrTokens = tokenise(trimmedPair.second);
    vector<string> substrPostfix = convertToPostfix(substrTokens, 0);
    if (!isPartialMatch) {
        return rhsTokensVec == substrTokens;
    } else {
        return includes(rhsTokensVec.begin(), rhsTokensVec.end(),
                        substrPostfix.begin(), substrPostfix.end());
    }
}


Result PatternHandler::evalPattern(PatternClause patternClause, ResultTable &resultTable,
                                   std::multimap<std::string, std::string> &synonymTable) {

    string patternSynon = patternClause.getPatternSynonym();
    string leftArg = patternClause.getLeftArg();
    string rightArg = patternClause.getRightArg();
    string leftType = Utility::getReferenceType(leftArg);
    string rightType = Utility::getReferenceType(rightArg);
    Result result;
    string patternType = synonymTable.find(patternSynon)->second;

    resultTableCheckAndAdd(patternSynon, resultTable, patternType);

    // Does the Design Entity represented by the pattern synon exist in PKB?
    // If not, set result to false
    if (resultTable.getValueFromKey(patternSynon).empty()) {
        result.setResultTrue(false);
        return result;
    }


    if (leftType == Utility::UNDERSCORE) {

        if (rightType == Utility::UNDERSCORE) {

            // result maintains current values of patternSynon
            result.setFirstArg(patternSynon, resultTable.getValueFromKey(patternSynon));

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            set<int> allAssignLineNums = pkb.getAllStmtNumsByType(Tokens::Keyword::ASSIGN);
            for (int assignLineNum : allAssignLineNums) {
                set<vector<string>>  allRHS = pkb.getPatternPostfixesFromStmt(assignLineNum);
                set<string> matchingLines = findMatchingLineNums(allRHS, rightArg);
                if (matchingLines.empty()) {
                    result.setResultTrue(false);
                    return result;
                }
                result.setFirstArg(patternSynon, matchingLines);
            }

        }

    } else if (leftType == Utility::SYNONYM) {

        string leftDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        std::set<string> currLeftSynonValues = resultTable.getValueFromKey(leftArg);

        // Does the Design Entity type represented by left synonym exist in PKB?
        // If not, set result to false
        if (currLeftSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }

        if (rightType == Utility::UNDERSCORE) {

            // result maintains current values of patternSynon and leftArg
            result.setFirstArg(patternSynon, resultTable.getValueFromKey(patternSynon));
            result.setSecondArg(leftArg, resultTable.getValueFromKey(leftArg));

        } else if (rightType == Utility::UNDERSCORED_EXPR) {
            std::set<string> resultPatternSynonVals;
            std::set<string> resultLeftSynonVals;

            for (string currLeftVal: currLeftSynonValues) {
                set<vector<string>> matchingRHS = pkb.getPatternPostfixesFromVar(currLeftVal);
                set<string> matchingLines = findMatchingLineNums(matchingRHS, rightArg);

                if (!matchingLines.empty()) {
                    resultLeftSynonVals.insert(currLeftVal);
                    for (string lineStr : matchingLines) {
                        resultPatternSynonVals.insert(lineStr);
                    }
                }
            }

            result.setFirstArg(patternSynon, resultPatternSynonVals);
            result.setSecondArg(leftArg, resultLeftSynonVals);
        }

    } else if (leftType == Utility::QUOTED_IDENT) {

        // Do SIMPLE expressions with LHS == stated leftArg exist in PKB?
        // If not, set result to false
        set<vector<string>> matchingRHS = pkb.getPatternPostfixesFromVar(leftArg);

        if (matchingRHS.empty()) {
            result.setResultTrue(false);
            return result;
        }

        if (rightType == Utility::UNDERSCORE) {
            std::set<string> resultPatternSynonVals;
            for (vector<string> rhsPostfix : matchingRHS) {
                set<int> lineNumSet = pkb.getPatternStmtsFromPostfix(rhsPostfix);
                for (int num : lineNumSet) {
                    resultPatternSynonVals.insert(to_string(num));
                }
            }

            result.setFirstArg(patternSynon, resultPatternSynonVals);

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            set<string> matchingLines = findMatchingLineNums(matchingRHS, rightArg);
            if (matchingLines.empty()) {
                result.setResultTrue(false);
                return result;
            }

            result.setFirstArg(patternSynon, matchingLines);

        }

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}



// Return a pair, where first element boolean = true if input is asking for partial match (e.g. _"x"_)
//, and false if input is aksing for full match (e.g. "x")
// Second element string is input trimmed of underscore and quotes
pair<bool,string> PatternHandler::trimUnderscoreQuotes(string input) {
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

    return make_pair(isPartialMatch, trimmed);

}


