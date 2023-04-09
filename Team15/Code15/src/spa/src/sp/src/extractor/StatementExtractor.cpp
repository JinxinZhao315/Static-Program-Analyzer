#include "sp/include/extractor/StatementExtractor.h"

void insertLineNumber(unordered_map<KeywordsEnum, set<int>>* statements, KeywordsEnum type, int* lineNumber) {
    statements->at(type).insert(*lineNumber);
}

bool isStatement(Line line) {
    return line.getType() == READ
           || line.getType() == PRINT
           || line.getType() == CALL
           || line.getType() == WHILE
           || line.getType() == IF
           || line.getType() == ASSIGN;
}

unordered_map<KeywordsEnum, set<int>> extractStatements(const vector<Line>& program) {
    unordered_map<KeywordsEnum, set<int>> statements;
    statements[WHILE] = {};
    statements[IF] = {};
    statements[READ] = {};
    statements[PRINT] = {};
    statements[CALL] = {};
    statements[ASSIGN] = {};

    for(auto line: program) {
        if(isStatement(line)) {
            vector<string> tokens = line.getTokens();
            KeywordsEnum type = line.getType();
            int lineNumber = line.getLineNumber();
            unordered_map<KeywordsEnum, set<int>> *stmt = &statements;
            insertLineNumber(stmt, type, &lineNumber);
        }
    }
    return statements;
}
