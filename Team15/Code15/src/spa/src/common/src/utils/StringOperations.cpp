#include "common/include/utils/StringOperations.h"

pair<vector<string>, vector<string>> getLHSandRHSofAssignStatement(vector<string> tokens) {
    pair<vector<string>, vector<string>> split;
    split.first.push_back(tokens[0]);
    for (int i = 1; i < tokens.size(); i++) {
        split.second.push_back(tokens[i]);
    }
    return split;
}

string getVarNameFromReadStatement(vector<string> tokens) {
    return getSecondToken(tokens);
}

string getVarNameFromPrintStatement(vector<string> tokens) {
    return getSecondToken(tokens);
}

string getSecondToken(vector<string> tokens) {
    return tokens[1];
}

set<string> getVariablesFromStatement(vector<string> tokens, const set<string>& variables) {
    set<string> result;
    for (string token : tokens) {
        if (variables.count(token) > 0) {
            result.insert(token);
        }
    }
    return result;
}

int precedence(const string& c) {
    if (c == "-" || c == "+") {
        return 1;
    } else if (c == "*" || c == "/" || c == "%") {
        return 2;
    } else if (c == "^") {
        return 3;
    }
    return -1;
}

bool isOperator(string c) {
    return precedence(c) > 0;
}

bool isNumber(const string& num) {
    const regex pattern("-?[0-9]+(\\.[0-9]+)?");
    return regex_match(num, pattern);
}


vector<string> convertToPostfix(const vector<string>& tokens, const set<string>& variables) {
    vector<string> result;
    stack<string> s;
    for (const auto &token : tokens) {
        if (variables.count(token) || isNumber(token)) {
            result.push_back(token);
        } else if (isOperator(token)) {
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
        }
    }
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}