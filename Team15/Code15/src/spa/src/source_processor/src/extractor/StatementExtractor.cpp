#include "source_processor/include/extractor/StatementExtractor.h"

StatementExtractor::StatementExtractor() {
    statements["while"] = {};
    statements["if"] = {};
    statements["read"] = {};
    statements["print"] = {};
    statements["call"] = {};
    statements["="] = {};
}

void insertLineNumber(unordered_map<string, set<int>>* statements, string* type, int* lineNumber) {
    statements->at(*type).insert(*lineNumber);
}

void StatementExtractor::extractVariables(Line line) {
    set<string>* v = &this->variables;
    vector<string> tokens = line.getTokens();
    for(auto token = begin(tokens); token != end(tokens); token++) {
        if(*token == "=" && token != begin(tokens)) {
            v->insert(*(prev(token)));
        }
    }
}

void StatementExtractor::extractStatements(Line line) {
    vector<string> tokens = line.getTokens();
    string type = line.getType();
    int lineNumber = line.getLineNumber();
    unordered_map<string, set<int>> *stmt = &this->statements;
    insertLineNumber(stmt, &type, &lineNumber);
    if(type == "=" || type == "read") {
        extractVariables(line);
    }
}

unordered_map<string, set<int>> StatementExtractor::getStatements() {
    return statements;
}

set<string> StatementExtractor::getVariables() {
    return variables;
}
