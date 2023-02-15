#include "../../include/util/StringOperations.h"


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