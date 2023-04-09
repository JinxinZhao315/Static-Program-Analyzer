
#include "qps/include/evaluator/PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}

vector<string> PatternHandler::findMatchingLineNums(bool isPartialMatch, set<int> allStmtsWithLHS, const vector<string>& substrTokens) {
    vector <string> ret;
    for (int stmtNum : allStmtsWithLHS) {
        bool isMatch;
        set < vector<string>> exprSet = pkb.getAssignExprsFromStmt(stmtNum);
        for (vector<string> rhsTokensVec : exprSet) {
            if (!isPartialMatch) {
                isMatch = rhsTokensVec == substrTokens;
            }
            else {
                isMatch = findIsPartialMatch(rhsTokensVec, substrTokens);
            }
            if (isMatch) {
                  ret.push_back(to_string(stmtNum));
            }
        }

    }
    return ret;
}


// Use sliding window to determine if substr is a subset of fullstr
bool PatternHandler::findIsPartialMatch(vector<string> fullstrVec, vector<string> substrVec) {
    size_t subStrSize = substrVec.size();
    size_t fullStrSize = fullstrVec.size();
    if (subStrSize > fullStrSize) {
        return false;
    }
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

set<int> PatternHandler::getLineNumsFromPkb(DesignEntity patternSynonType, const string& arg, const string& type) {
    set<int> lineNumSet;
    if (type == GET_FROM_VAR) {
        if (patternSynonType == ASSIGN_ENTITY) {
            lineNumSet = pkb.getAssignStmtsFromVar(arg);
        } else if (patternSynonType == WHILE_ENTITY) {
            lineNumSet = pkb.getWhileStmtsFromVar(arg);
        } else {
            lineNumSet = pkb.getIfStmtsFromVar(arg);
        }
    } else {
        if (patternSynonType == ASSIGN_ENTITY) {
            lineNumSet = pkb.getAllStmtNumsByType(ASSIGN);
        } else if (patternSynonType == WHILE_ENTITY) {
            lineNumSet = pkb.getWhileStmtsWithVars();
        } else {
            lineNumSet = pkb.getIfStmtsWithVars();
        }
    }
    return lineNumSet;
}


Result PatternHandler::evaluate(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable,
    int& synEvalPosition, std::vector<std::string>evalSynList) {

    string patternSynon = patternClause.getPatternSynonym();
    string firstArg = patternClause.getFirstArg();
    string secondArg = patternClause.getSecondArg();
    ReferenceType firstType = Utility::getEnumReferenceType(firstArg);
    ReferenceType secondType = Utility::getEnumReferenceType(secondArg);

    Result result;
    string patternType = synonymTable.find(patternSynon)->second;


    DesignEntity patternTypeEnum = Utility::getDesignEntityFromString(patternType);

    bool isPartialMatch;
    if (secondType == UNDERSCORED_EXPR) {
        isPartialMatch = true;
    } else  {
        isPartialMatch = false;
    }

    vector<string> secondArgPostfix;
    if (secondType == EXPR || secondType == UNDERSCORED_EXPR || secondType == QUOTED_IDENT) {
        string secondArgTrimmed = trimExpr(secondArg);
        vector<string> argTokens = simplifiedTokenise(secondArgTrimmed);
        secondArgPostfix = simplifiedConvertToPostfix(argTokens);
    }

    if (firstType == UNDERSCORE) {

        std::vector<std::string> resultPatternSynonVals;
        std::set<int> currPatternSynonVals = getLineNumsFromPkb(patternTypeEnum, Utility::empty, GET_ALL);

        if (secondType == UNDERSCORE) {
            for (int num : currPatternSynonVals) {
                resultPatternSynonVals.push_back(to_string(num));
            }

        } else {
            vector<string> matchingLines = findMatchingLineNums(isPartialMatch, currPatternSynonVals, secondArgPostfix);
            resultPatternSynonVals = matchingLines;
        }


        result.setClauseResult(ResultTable(resultPatternSynonVals, patternSynon));

    } else if (firstType == SYNONYM) {

        string firstDeType = synonymTable.find(firstArg)->second;
        std::set<string> currFirstSynonValues = resultTable.containsSyn(firstArg)
            ? resultTable.getSynValues(firstArg)
            : Utility::getResultFromPKB(pkb, firstDeType);

        ResultTable tempTable({patternSynon, firstArg });

        if (secondType == UNDERSCORE) {

            for (const string& currFirstVal: currFirstSynonValues) {
                    set<int> lineNumSet = getLineNumsFromPkb(patternTypeEnum, currFirstVal, GET_FROM_VAR);
                    // If second arg is wildcard, get every assign/while/if from pkb whose LHS is currFirstVal (a variable)
                    for (auto num : lineNumSet) { // Each num is a possible value of pattern synon
                        tempTable.insertTuple({to_string(num), currFirstVal});
                    }
            }

        } else {

            for (const string& currFirstVal: currFirstSynonValues) {
                set<int> allStmtWithLHS = pkb.getAssignStmtsFromVar(currFirstVal);
                vector<string> matchingLines = findMatchingLineNums(isPartialMatch, allStmtWithLHS, secondArgPostfix);
                if (!matchingLines.empty()) {
                    for (const string& lineStr : matchingLines) {
                        tempTable.insertTuple({lineStr, currFirstVal });
                    }
                }
            }
        }

        result.setClauseResult(tempTable);

    } else if (firstType == QUOTED_IDENT) {

        string firstArgTrimmed = trimExpr(firstArg);
        std::vector<std::string> patternSynonVals;


        if (secondType == UNDERSCORE) {
            set<int> lineNumSet = getLineNumsFromPkb(patternTypeEnum, firstArgTrimmed, GET_FROM_VAR);
            for (int lineNum : lineNumSet) {
                patternSynonVals.push_back(to_string(lineNum));
            }
            
            // If second arg is wildcard, get every assign/while/if from pkb whose LHS is firstArgTrimmed (a variable)

        } else {
            set<int> allStmtWithLHS = pkb.getAssignStmtsFromVar(firstArgTrimmed);
            vector<string> matchingLines = findMatchingLineNums(isPartialMatch, allStmtWithLHS, secondArgPostfix);
            for (const string& lineStr : matchingLines) {
                patternSynonVals.push_back(lineStr);
            }
        }

        result.setClauseResult(ResultTable(patternSynonVals, patternSynon));

    } else {
        throw PQLSyntaxError("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}


// ------- Helper functions -----
vector<string> PatternHandler::simplifiedTokenise(const string& input) {
    vector<string> tokens;
    std::string current_token;

    for (char c : input) {
        if (c == Utility::spaceChar || c == Utility::tabChar || c == Utility::nextLineChar) {
            continue;
        } else if (c == Utility::plusSignChar || c == Utility::minusSignChar || c == Utility::timesSignChar || c == Utility::divideSignChar
            || c == Utility::moduleSignChar || c == Utility::leftRoundBracketChar || c == Utility::rightRoundBracketChar) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.emplace_back(1, c);
        } else if (isalnum(c)) {
            current_token.push_back(c);
        } else {
            throw PQLSyntaxError("PQL Syntax Error: Invalid symbol in pattern expression");
        }
    }

    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    return tokens;
}

bool PatternHandler::isValidExprTerm(const string& token) {
    return regex_match(token, regex(Utility::synonymFormat)) // SynonymFormat is the same as a legal var format in SIMPLE
           || regex_match(token, regex(Utility::integerFormat));
}

bool PatternHandler::isValidStart(const string &token) {
    return isValidExprTerm(token) || token == Utility::leftRoundBracket;
}

bool PatternHandler::isValidEnd(const string &token) {
    return isValidExprTerm(token) || token == Utility::rightRoundBracket;
}

vector<string> PatternHandler::simplifiedConvertToPostfix(vector<string> tokens) {
    vector<string> result;
    stack<string> s;
    if (tokens.empty()) {
        throw PQLSyntaxError("PQL Syntax Error: empty expression in pattern clause");
    }
    // To prevent dangling operators like exprFormat = "+2"
    if (! (isValidStart(tokens.front()) && isValidEnd(tokens.back()))) {
        throw PQLSyntaxError("PQL Syntax Error: Invalid expression in pattern");
    }
    for (const string& token : tokens) {
        if (isValidExprTerm(token)) {
            result.push_back(token);
        } else if (token == Utility::plusSign || token == Utility::minusSign || token == Utility::timesSign || token == Utility::divideSign || token == Utility::moduleSign) {
            while (!s.empty() && precedence(s.top()) >= precedence(token)) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(token);
        } else if (token == Utility::leftRoundBracket) {
            s.push(token);
        } else if (token == Utility::rightRoundBracket) {
            while (s.top() != Utility::leftRoundBracket) {
                result.push_back(s.top());
                s.pop();
            }
            s.pop();
        } else {
            throw PQLSyntaxError("PQL Syntax Error: Invalid symbol in pattern expression");
        }
    }
    while (!s.empty()) {
        if (s.top() == Utility::leftRoundBracket) {
            throw PQLSyntaxError("PQL Syntax Error: Unclosed bracket in pattern expression");
        }
        result.push_back(s.top());
        s.pop();
    }
    return result;
}


std::string PatternHandler::trimExpr(string input) {
    std::string trimmed = input;
    trimmed = Utility::trim(trimmed, Utility::underscore);
    trimmed = Utility::trim(trimmed, Utility::whiteSpaces);
    trimmed = Utility::trim(trimmed, Utility::quote);
    trimmed = Utility::trim(trimmed, Utility::whiteSpaces);
    return trimmed;
}


