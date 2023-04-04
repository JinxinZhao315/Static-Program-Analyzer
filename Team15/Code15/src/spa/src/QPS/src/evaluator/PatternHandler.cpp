
#include "QPS/include/evaluator/PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}


set<string> PatternHandler::findMatchingLineNums(bool isPartialMatch, const set<vector<string>>& allRHS, const vector<string>& substrTokens) {
    set <string> ret;
    for (const vector<string>& rhsTokensVec : allRHS) {
        bool isMatch;
        if (!isPartialMatch) {
            isMatch = rhsTokensVec == substrTokens;
        } else {
            isMatch =  findIsPartialMatch(rhsTokensVec, substrTokens);
        }
        if (isMatch) {
            set<int> lineNumSet = pkb.getAssignStmtsFromExpr(rhsTokensVec);
            for (int num : lineNumSet) {
                ret.insert(to_string(num));
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

vector<string> PatternHandler::getLineNumsFromPkb(DesignEntity patternSynonType, const string& arg, const string& type) {
    set<int> lineNumSet;
    vector<string> strVec;
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

    for (int num : lineNumSet) {
        strVec.push_back(to_string(num));
    }
    return strVec;
}


Result PatternHandler::evaluate(PatternClause patternClause, ResultTable& resultTable, std::multimap<std::string, std::string>& synonymTable) {

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
    if (secondType == EXPR || secondType == UNDERSCORED_EXPR) {
        string secondArgTrimmed = trimExpr(secondArg);
        vector<string> argTokens = simplifiedTokenise(secondArgTrimmed);
        secondArgPostfix = simplifiedConvertToPostfix(argTokens);
    }

    if (firstType == UNDERSCORE) {

        std::vector<std::string> resultPatternSynonVals;
        std::vector<std::string> currPatternSynonVals = getLineNumsFromPkb(patternTypeEnum, "", GET_ALL);

        if (secondType == UNDERSCORE) {

            resultPatternSynonVals = currPatternSynonVals;

        } else {

            for (auto lineNum : currPatternSynonVals) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromStmt(stoi(lineNum));
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
                if (!matchingLines.empty()) {
                    resultPatternSynonVals.push_back(lineNum);
                }
            }
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
                    vector<string> lineNumVec = getLineNumsFromPkb(patternTypeEnum, currFirstVal, GET_FROM_VAR);
                    // If second arg is wildcard, get every assign/while/if from pkb whose LHS is currFirstVal (a variable)
                    for (const string& numStr : lineNumVec) { // Each num is a possible value of pattern synon
                        tempTable.insertTuple({numStr, currFirstVal});
                    }
            }

        } else {

            for (const string& currFirstVal: currFirstSynonValues) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromVar(currFirstVal);
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
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

            patternSynonVals = getLineNumsFromPkb(patternTypeEnum, firstArgTrimmed, GET_FROM_VAR);
            // If second arg is wildcard, get every assign/while/if from pkb whose LHS is firstArgTrimmed (a variable)

        } else {
            set<vector<string>> allRHS = pkb.getAssignExprsFromVar(firstArgTrimmed);
            set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
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
        if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        } else if (c == '+' || c == '-' || c == '*' || c == '/'
            || c == '%' || c == '(' || c == ')') {
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
    return isValidExprTerm(token) || token == "(";
}

bool PatternHandler::isValidEnd(const string &token) {
    return isValidExprTerm(token) || token == ")";
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
        } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%") {
            while (!s.empty() && precedence(s.top()) >= precedence(token)) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(token);
        } else if (token == "(") {
            s.push(token);
        } else if (token == ")") {
            while (s.top() != "(") {
                result.push_back(s.top());
                s.pop();
            }
            s.pop();
        } else {
            throw PQLSyntaxError("PQL Syntax Error: Invalid symbol in pattern expression");
        }
    }
    while (!s.empty()) {
        if (s.top() == "(") {
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
    trimmed = Utility::trim(trimmed, Utility::quote);
    trimmed = Utility::trim(trimmed, Utility::whiteSpaces);
    return trimmed;
}


