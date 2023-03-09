
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

vector<string> PatternHandler::simplifiedTokenise(string input) {
    vector<string> tokens;
    std::string current_token;

    for (int i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c == '+' || c == '-' || c == '*' || c == '/'
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

bool PatternHandler::isValidExprTerm(string token) {
    return regex_match(token, regex(Utility::synonymFormat)) // SynonymFormat is the same as a legal var format in SIMPLE
           || regex_match(token, regex(Utility::integerFormat));
}


vector<string> PatternHandler::simplifiedConvertToPostfix(vector<string> tokens) {
    vector<string> result;
    stack<string> s;
    if (tokens.empty()) {
        throw PQLSyntaxError("PQL Syntax Error: empty expression in pattern clause");
    }
    // To prevent dangling operators like expr = "+2"
    if (! (isValidExprTerm(tokens.front()) && isValidExprTerm(tokens.back()))) {
        throw PQLSyntaxError("PQL Syntax Error: Invalid expression in pattern");
    }
    for (string token : tokens) {
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



bool PatternHandler::findIsMatch(bool isPartialMatch, vector<string> rhsTokensVec, string substrToMatch) {
    string trimmed = trimExpr(substrToMatch);
    vector<string> substrTokens = simplifiedTokenise(trimmed);
    vector<string> substrPostfix = simplifiedConvertToPostfix(substrTokens);
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

vector<string> PatternHandler::getStmtsFromPkb(string patternSynonType, string arg, string type) {
    set<int> lineNumSet;
    vector<string> strVec;
    if (type == GET_FROM_VAR) {
        if (patternSynonType == "assign") {
            lineNumSet = pkb.getAssignStmtsFromVar(arg);
        } else if (patternSynonType == "while") {
            lineNumSet = pkb.getWhileStmtsFromVar(arg);
        } else { // if (patternSynonType == "if")
            lineNumSet = pkb.getIfStmtsFromVar(arg);
        }
    } else { // type == GET_ALL
        if (patternSynonType == "while") {
            lineNumSet = pkb.getWhileStmtsWithVars();
        } else { // if (patternSynonType == "if")
            lineNumSet = pkb.getIfStmtsWithVars();
        }
    }

    for (int num : lineNumSet) {
        strVec.push_back(to_string(num));
    }
    return strVec;
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
            if (patternType == "assign") {
                // result maintains current values of patternSynon, which is a assign synon
                // No need to call PKB since all eligible assign synon values are already in resultTable
                patternSynonVals = resultTable.getSynValues(patternSynon);
            } else {
                patternSynonVals = getStmtsFromPkb(patternType, "", GET_ALL);
            }

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
                    vector<string> lineNumVec = getStmtsFromPkb(patternType, currFirstVal, GET_FROM_VAR);
                    // If second arg is wildcard, get every assign/while/if from pkb whose LHS is currFirstVal (a variable)
                    for (string numStr : lineNumVec) { // Each num is a possible value of pattern synon
                        tempResultTable.insertTuple({numStr, currFirstVal});
                    }
            }

        } else {

            for (string currFirstVal: currFirstSynonValues) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromVar(currFirstVal);
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArg);
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

            patternSynonVals = getStmtsFromPkb(patternType, firstArgTrimmed, GET_FROM_VAR);
            // If second arg is wildcard, get every assign/while/if from pkb whose LHS is firstArgTrimmed (a variable)

        } else {
            set<vector<string>> allRHS = pkb.getAssignExprsFromVar(firstArgTrimmed);
            set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArg);
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


