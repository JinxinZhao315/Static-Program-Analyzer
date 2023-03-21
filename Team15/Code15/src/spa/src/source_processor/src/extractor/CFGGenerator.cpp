#include "source_processor/include/extractor/CFGGenerator.h"

unordered_map<int, set<int>> generateCFG(const vector<Line>& program) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }

    stack<pair<int, string>> nestingStack;
    vector<int> nodesToJoin;
    int prevLineNumber = -1;
    int currMaxLineNumber = 0;
    int nextLineNumber = 0;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        currMaxLineNumber = max(currMaxLineNumber, lineNumber);
        nextLineNumber = currMaxLineNumber + 1;
        bool isPrevLineValid = prevLineNumber != -1 && prevLineNumber != lineNumber;
        if (lineType == "procedure") {
            nestingStack = stack<pair<int, string>>(); // clear stack
            nodesToJoin.clear();
            prevLineNumber = -1;
            continue;
        } else if (lineType == "if" || lineType == "while") {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
            cfg[lineNumber].insert(nextLineNumber);
            prevLineNumber = -1;
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
                    nodesToJoin.push_back(prevLineNumber);
                } else if (parentType == "while") {
                    nodesToJoin.push_back(parentLine);
                    cfg[prevLineNumber].insert(parentLine); // link back to head of while loop
                }
                if (!nodesToJoin.empty() && i + 1 < program.size()) {
                    string nextLineType = program[i + 1].getType();
                    if(nextLineType != "}" && nextLineType != "else") {
                        for (int lineToLink: nodesToJoin) {
                            cfg[lineToLink].insert(nextLineNumber); // link all nodes to next line
                        }
                        nodesToJoin.clear(); // clear the nodes to join
                    }
                }
                nestingStack.pop();
            }
            prevLineNumber = -1;
        } else {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
        }


        if (lineNumber > 0) {
            prevLineNumber = lineNumber;
        }
    }

    return cfg;
}
