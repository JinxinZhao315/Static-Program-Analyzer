#include "source_processor/include/extractor/VariableExtractor.h"

VariableExtractor::VariableExtractor() {
    keywords = new Keywords();
}

bool isNumeric(const string& token) {
    try {
        stoi(token);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool VariableExtractor::isVariable(string token, string previous) {
    if(keywords->isKeyword(token) || isNumeric(token) || token.empty()) {
        return false;
    } else if(previous != "procedure" && previous != "call") {
        return true;
    } else {
        return false;
    }
}

void VariableExtractor::extractVariables(const vector<Line> &program) {
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        string type = line.getType();
        set<string>* v = &variables;
        for(auto token = begin(tokens) + 1; token != end(tokens); token++) {
            if(isVariable(*token, *prev(token))) {
                v->insert(*token);
            } else if(*token == "=" && token != begin(tokens)) {
                v->insert(*(prev(token)));
            } else if (*token == "read" && token != end(tokens)) {
                v->insert(*next(token));
            }
        }
    }
}

bool VariableExtractor::findVariable(string token) {
    for(auto variable : variables) {
        if(variable == token) return true;
    }
    return false;
}

void VariableExtractor::extractReadAndPrintLineNumToVarName(const vector<Line> &program) {
    for(auto line : program) {
        vector<string> tokens = line.getTokens();
        string type = line.getType();
        int lineNumber = line.getLineNumber();
        for(auto token : tokens) {
            if(findVariable(token)) {
                if(type == "read") {
                    readLineNumToVarName[lineNumber] = token;
                } else {
                    printLineNumToVarName[lineNumber] = token;
                }
            }
        }
    }
}

set<string> VariableExtractor::getVariables() {
    return variables;
}

unordered_map<int, string> VariableExtractor::getReadLineNumToVarName() {
    return readLineNumToVarName;
}

unordered_map<int, string> VariableExtractor::getPrintLineNumToVarName() {
    return readLineNumToVarName;
}
