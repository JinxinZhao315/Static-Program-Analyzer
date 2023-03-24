#include "source_processor/include/extractor/CFGGenerator.h"

unordered_map<int, set<int>> generateCFG(const vector<Line>& program) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }
    // intermediate data structures for each procedure
    stack<pair<int, string>> nestingStack;
    vector<int> nodesToJoin;
    bool prevLineHasNumber = false;
    int prevLineNumber = -1;
    int currMaxLineNumber = 0;
    int nextLineNumber;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        currMaxLineNumber = max(currMaxLineNumber, lineNumber);
        nextLineNumber = currMaxLineNumber + 1;
        bool isPrevLineValid = prevLineHasNumber && prevLineNumber != lineNumber;
        if (lineType == "procedure") {
            nestingStack = stack<pair<int, string>>(); // clear stack
            nodesToJoin.clear();
            prevLineHasNumber = false;
            continue;
        } else if (lineType == "if" || lineType == "while") {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
            nodesToJoin.clear(); // clear nodesToJoin for new nesting level
            cfg[lineNumber].insert(nextLineNumber);
            prevLineHasNumber = false;
        } else if (lineType == "else") {
            auto [parentLine, parentType] = nestingStack.top();
            cfg[parentLine].insert(nextLineNumber);
            nodesToJoin.push_back(prevLineNumber);
            prevLineHasNumber = false;
        } else if (lineType == "}") {
            if (!nestingStack.empty()) {
                auto [parentLine, parentType] = nestingStack.top();
                if (parentType == "if") {
                    nodesToJoin.push_back(prevLineNumber);
                } else if (parentType == "while") {
                    cfg[prevLineNumber].insert(parentLine); // link back to head of while loop
                    // todo: put this 4 lines in correct spot
                    for (int lineToLink: nodesToJoin) {
                        cfg[lineToLink].insert(parentLine); // link all nodes to next line
                    }
                    nodesToJoin.clear(); // clear the nodes to join
                    nodesToJoin.push_back(parentLine);
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
            prevLineHasNumber = false;
        } else {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
        }


        if (lineNumber > 0) {
            prevLineHasNumber = true;
            prevLineNumber = lineNumber;
        }
    }

    return cfg;
}
