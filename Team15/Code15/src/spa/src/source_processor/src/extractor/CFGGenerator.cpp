#include "source_processor/include/extractor/CFGGenerator.h"



void printNodes(const map<int, set<int>>& myMap) {
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": [";
        for (const auto& v : value) {
            std::cout << v << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

map<int, set<int>> generateCFG(const vector<Line>& program) {
    map<int, set<int>> cfg;
    if (program.size() < 2) {
        return cfg;
    }

    struct StackEntry {
        int lineNumber;
        string lineType;
        int endOfThen;
    };

    stack<StackEntry> stack;
    stack.push({-1, "", 0});
    int prevLineNumber = -1;

    for (int i = 1; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();

        int nextLineNumber = lineNumber + 1;

        StackEntry &entry = stack.top();

        if (lineType == "procedure") {
            stack.push({lineNumber, "procedure", 0});
            prevLineNumber = -1;
        } else if (lineType == "if" || lineType == "while") {
            cfg[prevLineNumber].insert(lineNumber);
            stack.push({lineNumber, lineType, 0});
            prevLineNumber = -1;
        } else if (lineType == "else") {
            entry.endOfThen = prevLineNumber;
            cfg[prevLineNumber].insert(nextLineNumber);
            prevLineNumber = -1;
        } else if (lineType == "}") {
            if (entry.lineType == "while") {
                cfg[prevLineNumber].insert(entry.lineNumber);
                cfg[entry.lineNumber].insert(nextLineNumber);
            } else if (entry.lineType == "if") {
                cfg[entry.endOfThen].insert(nextLineNumber);
                cfg[prevLineNumber].insert(nextLineNumber);
            }
            stack.pop();
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

