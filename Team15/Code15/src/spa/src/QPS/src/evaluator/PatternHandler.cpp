
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

    // Is the values of patternSynon in result table empty?
    // If yes, set result to false
    if (!resultTable.isSynonymPresent(patternSynon)) {
        result.setResultTrue(false);
        return result;
    }


    if (leftType == Utility::UNDERSCORE) {

        std::unordered_map<std::string, SynonymLinkageMap> patternSynonVals;

        if (rightType == Utility::UNDERSCORE) {

            // result maintains current values of patternSynon
            patternSynonVals = resultTable.getSynonymEntry(patternSynon);

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            set<string> patternSynonLineNums = resultTable.getStringSetFromKey(patternSynon);

            for (string lineNum : patternSynonLineNums) {
                set<vector<string>> allRHS = pkb.getPatternPostfixesFromStmt(stoi(lineNum));
                set<string> matchingLines = findMatchingLineNums(allRHS, rightArg);
                if (!matchingLines.empty()) {
                    patternSynonVals.insert(make_pair(
                            lineNum,
                            SynonymLinkageMap()));
                }
            }
        }

        result.setFirstArg(patternSynon, patternSynonVals);

    } else if (leftType == Utility::SYNONYM) {

        string leftDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        std::set<string> currLeftSynonValues = resultTable.getStringSetFromKey(leftArg);

        // Does the Design Entity type represented by left synonym exist in PKB?
        // If not, set result to false
        if (currLeftSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }

        std::unordered_map<std::string, SynonymLinkageMap> patternSynonVals;
        std::unordered_map<std::string, SynonymLinkageMap> leftSynonVals;

        if (rightType == Utility::UNDERSCORE) {

            for (string currLeftVal: currLeftSynonValues) {
                set<vector<string>> matchingRHS = pkb.getPatternPostfixesFromVar(currLeftVal);
                // If right Arg is wildcard, every RHS in matchingRHS is a match. So no need to call findMatchingLines function.
                // If matchingRHS is not empty, it means leftArg (must be a var) is the LHS of some assignment(s)
                if (!matchingRHS.empty()) {
                    if (leftSynonVals.find(currLeftVal) == leftSynonVals.end()) {
                        leftSynonVals.insert(make_pair(currLeftVal, SynonymLinkageMap()));
                    }
                    set<int> lineNumSet = pkb.getPatternStmtsFromVar(currLeftVal);
                    for (int num : lineNumSet) {
                        string numStr = to_string(num);
                        if (patternSynonVals.find(numStr) == patternSynonVals.end()) {
                            patternSynonVals.insert(make_pair(numStr, SynonymLinkageMap()));
                        }
                        patternSynonVals.find(numStr)->second.insertLinkage(leftArg, currLeftVal);
                        leftSynonVals.find(currLeftVal)->second.insertLinkage(patternSynon, numStr);
                        //leftSynonVals.insert(currLeftVal);
                        //patternSynonVals.insert(to_string(num));
                    }

                }
            }

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            for (string currLeftVal: currLeftSynonValues) {
                set<vector<string>> matchingRHS = pkb.getPatternPostfixesFromVar(currLeftVal);
                set<string> matchingLines = findMatchingLineNums(matchingRHS, rightArg);
                if (!matchingLines.empty()) {

                    if (leftSynonVals.find(currLeftVal) == leftSynonVals.end()) {
                        leftSynonVals.insert(make_pair(currLeftVal, SynonymLinkageMap()));
                    }
                    for (string lineStr : matchingLines) {
                        if (patternSynonVals.find(lineStr) == patternSynonVals.end()) {
                            patternSynonVals.insert(make_pair(lineStr, SynonymLinkageMap()));
                        }
                        patternSynonVals.find(lineStr)->second.insertLinkage(leftArg, currLeftVal);
                        leftSynonVals.find(currLeftVal)->second.insertLinkage(patternSynon, lineStr);
                        //leftSynonVals.insert(currLeftVal);
                        //patternSynonVals.insert(lineStr);
                    }

                }
            }
        }

        result.setFirstArg(patternSynon, patternSynonVals);
        result.setSecondArg(leftArg, leftSynonVals);

    } else if (leftType == Utility::QUOTED_IDENT) {

        // Do SIMPLE expressions with LHS == stated leftArg exist in PKB?
        // If not, set result to false
        string leftArgTrimmed = trimPattern(leftArg).second;
        set<vector<string>> matchingRHS = pkb.getPatternPostfixesFromVar(leftArgTrimmed);

        if (matchingRHS.empty()) {
            result.setResultTrue(false);
            return result;
        }

        std::unordered_map<std::string, SynonymLinkageMap> patternSynonVals;

        if (rightType == Utility::UNDERSCORE) {

            set<int> lineNumSet = pkb.getPatternStmtsFromVar(leftArgTrimmed);
            for (int num : lineNumSet) {
                patternSynonVals.insert(make_pair(
                        to_string(num),
                        SynonymLinkageMap()
                        ));
            }

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            set<string> matchingLines = findMatchingLineNums(matchingRHS, rightArg);
            if (matchingLines.empty()) {
                result.setResultTrue(false);
                return result;
            } else {
                for (string lineStr : matchingLines) {
                    patternSynonVals.insert(make_pair(
                            lineStr,
                            SynonymLinkageMap()
                    ));
                }
            }
        }

        result.setFirstArg(patternSynon, patternSynonVals);

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


