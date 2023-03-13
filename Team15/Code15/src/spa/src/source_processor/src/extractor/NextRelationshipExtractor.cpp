#include "source_processor/include/extractor/NextRelationshipExtractor.h"

bool hasLineNumber(string keyword) {
    return !(keyword == "procedure" || keyword == "else" || keyword == "}");
}

bool containsToken(vector<string> tokens, string token) {
    return find(tokens.begin(), tokens.end(), token) != tokens.end();
}

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program) {
    unordered_map<int, set<int>> nextRS;
    unordered_map<int, set<int>> currentProcNextRS;
    int prevLineNumber = 0;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        string type = line.getType();
        int currLineNumber = line.getLineNumber();
        if(type == "procedure") {
            nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
            currentProcNextRS.clear();
        } else if(currLineNumber > 1) {
            currentProcNextRS[prevLineNumber].insert(currLineNumber);
        } if (type == "if") {
            // TODO: rethink this logic
        } else if (type == "while") {
            // get the line number of the first line after the while
            int newLineNumber = currLineNumber;
            int nesting = 1;
            for(int j = i + 1; j < program.size(); j++) {
                Line newLine = program[j];
                string newLineType = newLine.getType();
                vector<string> newTokens = newLine.getTokens();
                if (containsToken(newTokens, "{")) {
                    nesting++;
                } else if (newLineType == "}") {
                    nesting--;
                    if(nesting == 0) {
                        for(auto entry : currentProcNextRS) {
                            if(entry.second.find(currLineNumber) != entry.second.end()) {
                                currentProcNextRS[entry.first].insert(newLineNumber + 1);
                            }
                        }
                    }
                }
                if(hasLineNumber(newLineType)) {
                    newLineNumber++;
                }
            }
        }
        if(hasLineNumber(type)) {
            prevLineNumber++;
        }
    }
    nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
    currentProcNextRS.clear();
    return nextRS;
}