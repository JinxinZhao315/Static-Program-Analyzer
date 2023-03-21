#include "source_processor/include/extractor/CFGGenerator.h"

unordered_map<int, set<int>> generateCFG(const vector<Line>& program) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }

    stack<pair<int, string>> nestingStack;
    vector<int> nodesToJoin;
    int prevLineNumber = -1;
    int maxLineNumber = 0; // todo: check if needed
    for (auto line: program) {
        maxLineNumber = max(maxLineNumber, line.getLineNumber());
    }

    for (auto line : program) {
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        int nextLineNumber = lineNumber + 1;
        bool isPrevLineValid = prevLineNumber != -1 && prevLineNumber != lineNumber;
        if (lineType == "if" || lineType == "while") {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
            cfg[nextLineNumber].insert(lineNumber);
            prevLineNumber = -1; //todo: check this
        } else if (lineType == "else") {
            if (!nestingStack.empty()) {
                int parentLine;
                string parentType;
                tie(parentLine, parentType) = nestingStack.top();
                cfg[parentLine].insert(nextLineNumber);
            }
            nodesToJoin.push_back(prevLineNumber);
            prevLineNumber = -1;
        } else if (lineType == "}") {
            if (!nestingStack.empty()) {
                int parentLine;
                string parentType;
                tie(parentLine, parentType) = nestingStack.top();
                if (parentType == "if") {
                    int parentLineNumber;
                    string parentLineType;
                    tie(parentLineNumber, parentLineType) = nestingStack.top();
                    if (parentLineNumber != 0) {
                        cfg[parentLineNumber].insert(nextLineNumber);
                    }
                    nodesToJoin.push_back(lineNumber);
                } else if (parentType == "while" && nextLineNumber != 0) {
                    nodesToJoin.push_back(parentLine);
                    cfg[lineNumber].insert(parentLine); // link back to head of while loop
                }
                nestingStack.pop();
            }

            prevLineNumber = -1;
        } else {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
        }

        if (nodesToJoin.size() > 0) {

        }

        if (lineNumber > 0) {
            prevLineNumber = lineNumber;
        }
    }

    return cfg;
}
