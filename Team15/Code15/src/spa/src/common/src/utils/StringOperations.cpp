#include <utility>

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
    return getSecondToken(std::move(tokens));
}

string getVarNameFromPrintStatement(vector<string> tokens) {
    return getSecondToken(std::move(tokens));
}

string getProcedureNameFromProcedureStatement(vector<string> tokens) {
    return getSecondToken(std::move(tokens));
}

string getProcedureNameFromCallStatement(vector<string> tokens) {
    return getSecondToken(std::move(tokens));
}

string getSecondToken(vector<string> tokens) {
    return tokens[1];
}

set<string> getVariablesFromStatement(const vector<string>& tokens, const set<string>& variables) {
    set<string> result;
    for (const string& token : tokens) {
        if (variables.count(token) > 0) {
            result.insert(token);
        }
    }
    return result;
}

int precedence(const string& c) {
    if(c == "||") {
        return 1;
    } else if (c == "<" || c == ">" || c == "<=" || c == ">=" || c == "==" || c == "!=") {
        return 2;
    } else if (c == "&&") {
        return 3;
    } else if (c == "-" || c == "+") {
        return 4;
    } else if (c == "*" || c == "/" || c == "%") {
        return 5;
    } else if (c == "^") {
        return 6;
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

vector<string> simplifiedTokenise(string input) {
    vector<string> tokens;
    std::string current_token;

    for (int i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c == ';') {
            continue;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.emplace_back(1, c);
        } else if (isalnum(c)) {
            current_token.push_back(c);
        } else {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
        }
    }

    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    return tokens;
}