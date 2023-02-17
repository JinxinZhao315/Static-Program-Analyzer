#include "../../include/extractor/AssignsRelationshipExtractor.h"

int precedence(string c) {
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

bool isNumber(string num) {
    try {
        stod(num);
        return true;
    } catch (const invalid_argument &e) {
        return false;
    }
}

vector<string> convertToPostfix(vector<string> tokens, const set<string>& variables) {
    vector<string> result;
    stack<string> s;
    for (int i = 0; i < tokens.size(); i++) {
        string token = tokens[i];
        if (variables.count(token)) {
            result.push_back(token);
        } else if (isOperator(tokens[i])) {
            while (!s.empty() && precedence(s.top()) >= precedence(token)) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        } else if (isNumber(token)) {
            result.push_back(token);
        }
    }
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

unordered_map<string, set<Line> > extractAssignmentRS(const vector<Line>& program, const set<string>& variables) {
    unordered_map<string, set<Line>> assignsRS;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();
        if (lineType != "=") continue;
        auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
        string varName = LHS[0];
        vector<string> postfixRHS = convertToPostfix(RHS, variables);
        Line newLine(currLineNumber, postfixRHS);
        if (assignsRS.count(varName) == 0) {
            assignsRS.emplace(varName, set<Line>({newLine}));
        } else {
            assignsRS[varName].insert(newLine);
        }
    }
    return assignsRS;
}