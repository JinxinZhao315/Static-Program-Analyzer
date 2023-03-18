#include "source_processor/include/extractor/CFGGenerator.h"

void printNodes(const unordered_map<int, set<int>>& myMap) {
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": [";
        for (const auto& v : value) {
            std::cout << v << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

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
            if (prevLineNumber != -1) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
            prevLineNumber = -1;
        } else if (lineType == "else") {
            if (!nestingStack.empty()) {
                int topLineNumber;
                string topLineType;
                tie(topLineNumber, topLineType) = nestingStack.top();
                cfg[topLineNumber].insert(nextLineNumber);
                nestingStack.pop();
                nestingStack.emplace(lineNumber, "else");
            }
            prevLineNumber = -1;
        } else if (lineType == "}") {
            if (!nestingStack.empty()) {
                int topLineNumber;
                string topLineType;
                tie(topLineNumber, topLineType) = nestingStack.top();
                cfg[topLineNumber].insert(nextLineNumber);
                nestingStack.pop();
                if (!nestingStack.empty() && topLineType != "else") {
                    cfg[nestingStack.top().first].insert(nextLineNumber);
                }
                if (topLineType == "while") {
                    cfg[nextLineNumber].insert(topLineNumber);
                }
            }
            prevLineNumber = -1;
        } else {
            if (prevLineNumber != -1) {
                cfg[prevLineNumber].insert(lineNumber);
            }
        }

        if (lineNumber > 0) {
            prevLineNumber = lineNumber;
        }
    }

    printNodes(cfg);
    return cfg;
}
