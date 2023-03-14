#include "source_processor/include/extractor/NextRelationshipExtractor.h"
#include "source_processor/include/extractor/CFGNode.h"

bool hasLineNumber(string keyword) {
    return !(keyword == "procedure" || keyword == "else" || keyword == "}");
}

bool containsToken(vector<string> tokens, string token) {
    return find(tokens.begin(), tokens.end(), token) != tokens.end();
}

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program) {
    unordered_map<int, set<int>> nextRS;
    unordered_map<int, set<int>> currentProcNextRS;
    unordered_map<int, CFGNode> cfgNodes;
    int prevLineNumber = 0;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        string type = line.getType();
        int currLineNumber = line.getLineNumber();
        if(type == "procedure") {
            nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
            currentProcNextRS.clear();
        } else if (type == "if" || type == "while") {
            // get the line number of the first line after the while
            currentProcNextRS[prevLineNumber].insert(currLineNumber);
            int newLineNumber = currLineNumber;
            int nesting = 1;
            for(int j = i + 1; j < program.size(); j++) {
                Line newLine = program[j];
                string newLineType = newLine.getType();
                vector<string> newTokens = newLine.getTokens();
                if (containsToken(newTokens, "{")) {
                    nesting++;
                    if(newLineType == "else") {
                        currentProcNextRS[currLineNumber].insert(newLineNumber + 1);
                    }
                } else if (newLineType == "}" || containsToken(newTokens, "}")) {
                    nesting--;
                    if(nesting == 0) {
                        currentProcNextRS[currLineNumber].insert(newLineNumber + 1);
                    }
                }
                if(hasLineNumber(newLineType)) {
                    newLineNumber++;
                }
            }
        } else if(currLineNumber > 1) {
            currentProcNextRS[prevLineNumber].insert(currLineNumber);
        }
        if(hasLineNumber(type)) {
            prevLineNumber++;
        }
    }
    nextRS.insert(currentProcNextRS.begin(), currentProcNextRS.end());
    currentProcNextRS.clear();
    return nextRS;
}
