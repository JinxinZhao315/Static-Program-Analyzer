#include "source_processor/include/extractor/CFGGenerator.h"

unordered_map<int, set<int>> generateCFG(const vector<Line>& program) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }

    stack<pair<int, string>> nestingStack;
    int prevLineNumber = -1;

    for (auto line : program) {
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        int nextLineNumber = lineNumber + 1;

        if (lineType == "if" || lineType == "while") {
            if (prevLineNumber != -1 && prevLineNumber != 0 && prevLineNumber != lineNumber) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
            prevLineNumber = -1;
        } else if (lineType == "else") {
            if (!nestingStack.empty()) {
                int topLineNumber;
                string topLineType;
                tie(topLineNumber, topLineType) = nestingStack.top();
                if (topLineNumber != 0) {
                    cfg[topLineNumber].insert(nextLineNumber);
                }
                nestingStack.pop();
                nestingStack.emplace(lineNumber, "else");
            }
            prevLineNumber = -1;
        } else if (lineType == "}") {
            if (!nestingStack.empty()) {
                int topLineNumber;
                string topLineType;
                tie(topLineNumber, topLineType) = nestingStack.top();
                if (topLineNumber != 0) {
                    cfg[topLineNumber].insert(nextLineNumber);
                }
                nestingStack.pop();
                if (!nestingStack.empty() && topLineType != "else") {
                    int parentLineNumber;
                    string parentLineType;
                    tie(parentLineNumber, parentLineType) = nestingStack.top();
                    if (parentLineNumber != 0) {
                        cfg[parentLineNumber].insert(nextLineNumber);
                    }
                }
                if (topLineType == "while" && nextLineNumber != 0) {
                    cfg[nextLineNumber].insert(topLineNumber);
                }
            }
            prevLineNumber = -1;
        } else {
            if (prevLineNumber != -1 && prevLineNumber != 0 && prevLineNumber != lineNumber) {
                cfg[prevLineNumber].insert(lineNumber);
            }
        }

        if (lineNumber > 0) {
            prevLineNumber = lineNumber;
        }
    }

    return cfg;
}
