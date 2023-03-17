
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

vector<string> PatternHandler::getStmtsFromPkb(const string& patternSynonType, const string& arg, const string& type) {
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


Result PatternHandler::evaluate(PatternClause patternClause, ResultTable &resultTable,
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

    vector<string> secondArgPostfix;
    if (secondType == Utility::EXPR || secondType == Utility::UNDERSCORED_EXPR) {
        string secondArgTrimmed = trimExpr(secondArg);
        vector<string> argTokens = simplifiedTokenise(secondArgTrimmed);
        secondArgPostfix = simplifiedConvertToPostfix(argTokens);
    }

    if (firstType == Utility::UNDERSCORE) {

        std::vector<std::string> patternSynonVals;

        if (secondType == Utility::UNDERSCORE) {
            if (patternType == "assign") {
                // Result maintains current values of patternSynon, which is a assign synon
                // No need to call PKB since all eligible assign synon values are already in resultTable
                patternSynonVals = resultTable.getSynValues(patternSynon);
            } else {
                patternSynonVals = getStmtsFromPkb(patternType, "", GET_ALL);
            }

        } else {
            std::vector<std::string> patternSynonLineNums = resultTable.getSynValues(patternSynon);

            for (const string& lineNum : patternSynonLineNums) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromStmt(stoi(lineNum));
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
                // TODO: Potential speed up here. Since we're only checking if matchingLines is empty or not,
                //  can ask pkb to just return a bool, instead of getting the whole set out
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

            for (const string& currFirstVal: currFirstSynonValues) {
                    vector<string> lineNumVec = getStmtsFromPkb(patternType, currFirstVal, GET_FROM_VAR);
                    // If second arg is wildcard, get every assign/while/if from pkb whose LHS is currFirstVal (a variable)
                    for (const string& numStr : lineNumVec) { // Each num is a possible value of pattern synon
                        tempResultTable.insertTuple({numStr, currFirstVal});
                    }
            }

        } else {

            for (const string& currFirstVal: currFirstSynonValues) {
                set<vector<string>> allRHS = pkb.getAssignExprsFromVar(currFirstVal);
                set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
                if (!matchingLines.empty()) {
                    for (const string& lineStr : matchingLines) {
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
            set<string> matchingLines = findMatchingLineNums(isPartialMatch, allRHS, secondArgPostfix);
            for (const string& lineStr : matchingLines) {
                patternSynonVals.push_back(lineStr);
            }
        }

        result.setClauseResult(ResultTable(patternSynonVals, patternSynon));

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
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
    trimmed = Utility::trim(trimmed, Utility::UNDERSCORE);
    trimmed = Utility::trim(trimmed, Utility::QUOTE);
    trimmed = Utility::trim(trimmed, Utility::WHITESPACES);
    return trimmed;
}


