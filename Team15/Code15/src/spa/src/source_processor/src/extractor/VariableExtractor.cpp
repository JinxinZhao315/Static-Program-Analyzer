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

bool VariableExtractor::isVariable(const string& token, const string& previous) {
    if(keywords->isKeyword(token) || isNumeric(token) || token.empty()) {
        return false;
    } else if(previous != keywords->keywordMap.second.at(PROCEDURE)
        && previous != keywords->keywordMap.second.at(CALL)) {
        return true;
    } else {
        return false;
    }
}

void VariableExtractor::extractVariables(const vector<Line> &program) {
    for(auto line: program) {
        vector<string> tokens = line.getTokens();
        set<string>* v = &variables;
        for(auto token = begin(tokens) + 1; token != end(tokens); token++) {
            if(isVariable(*token, *prev(token))) {
                v->insert(*token);
            } else if(*token == keywords->keywordMap.second.at(ASSIGN) && token != begin(tokens)) {
                v->insert(*(prev(token)));
            } else if (*token == keywords->keywordMap.second.at(READ) && token != end(tokens)) {
                v->insert(*next(token));
            }
        }
    }
}

void VariableExtractor::extractReadAndPrintLineNumToVarName(const vector<Line> &program) {
    for(auto line : program) {
        vector<string> tokens = line.getTokens();
        KeywordsEnum type = line.getType();
        int lineNumber = line.getLineNumber();
        for(const auto& token : tokens) {
            if(variables.count(token) > 0) {
                if(type == READ) {
                    readLineNumToVarName[lineNumber] = token;
                } else if (type == PRINT){
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
    return printLineNumToVarName;
}
