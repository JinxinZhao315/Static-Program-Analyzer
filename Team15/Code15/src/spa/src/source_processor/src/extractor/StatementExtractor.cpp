#include "source_processor/include/extractor/StatementExtractor.h"

void insertLineNumber(unordered_map<string, set<int>>* statements, string* type, int* lineNumber) {
    statements->at(*type).insert(*lineNumber);
}

bool isStatement(Line line) {
    return line.getType() == "read"
           || line.getType() == "print"
           || line.getType() == "call"
           || line.getType() == "while"
           || line.getType() == "if"
           || line.getType() == "=";
}

unordered_map<string, set<int>> extractStatements(const vector<Line>& program) {
    unordered_map<string, set<int>> statements;
    statements["while"] = {};
    statements["if"] = {};
    statements["read"] = {};
    statements["print"] = {};
    statements["call"] = {};
    statements["="] = {};

    for(auto line: program) {
        if(isStatement(line)) {
            vector<string> tokens = line.getTokens();
            string type = line.getType();
            int lineNumber = line.getLineNumber();
            unordered_map<string, set<int>> *stmt = &statements;
            insertLineNumber(stmt, &type, &lineNumber);
        }
    }
    return statements;
}
