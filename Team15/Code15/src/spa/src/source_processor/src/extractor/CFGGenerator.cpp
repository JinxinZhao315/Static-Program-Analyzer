#include "source_processor/include/extractor/CFGGenerator.h"

/**
 * To be used to get prevCFGNode when at the end of the if-then/else block and link it to the
 */
void linkEndOfBlock(const Line& prevLine, const pair<int, string>& justExited, const int& prevLineNumber, vector<int>& nodesToJoin) {
    if (prevLine.getType() == "}") {
        auto [parentLine, parentType] = justExited;
        if (parentType == "while") {
            nodesToJoin.push_back(parentLine);
        }
    } else {
        nodesToJoin.push_back(prevLineNumber);
    }
}

void linkPrevLines(unordered_map<int, set<int>>& cfg, vector<int>& nodesToJoin, int lineNumber) {
    for (int lineToLink: nodesToJoin) {
        cfg[lineToLink].insert(lineNumber); // link all nodes to next line
    }
    nodesToJoin.clear(); // clear the nodes to join
}

unordered_map<int, set<int>> generateCFG(const vector<Line>& program) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }
    // intermediate data structures for each procedure
    stack<pair<int, string>> nestingStack;
    vector<int> nodesToJoin;
    bool prevLineHasNumber = false;
    int prevLineNumber;
    int currMaxLineNumber = 0;
    int nextLineNumber;
    pair<int, string> justExited;
    for (int i = 0; i < program.size(); i++) {
        const Line& line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        currMaxLineNumber = max(currMaxLineNumber, lineNumber);
        nextLineNumber = currMaxLineNumber + 1;
        bool isPrevLineValid = prevLineHasNumber && prevLineNumber != lineNumber;


        if (lineType == "procedure") {
            nestingStack = stack<pair<int, string>>(); // clear stack
            nodesToJoin.clear();
            prevLineHasNumber = false;
            justExited = make_pair(0, "");;
            continue;
        } else if (lineType == "if" || lineType == "while") {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace(lineNumber, lineType);
//            nodesToJoin.clear(); // clear nodesToJoin for new nesting level
            cfg[lineNumber].insert(nextLineNumber);
            prevLineHasNumber = false;
        } else if (lineType == "else") {
            auto [parentLine, parentType] = nestingStack.top();
            cfg[parentLine].insert(nextLineNumber);
            linkEndOfBlock(program[i - 1], justExited, prevLineNumber, nodesToJoin);
            prevLineHasNumber = false;
        } else if (lineType == "}") {
            if (!nestingStack.empty()) {
                auto [parentLine, parentType] = nestingStack.top();
                if (parentType == "if") {
                    linkEndOfBlock(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                } else if (parentType == "while") {
                    cfg[prevLineNumber].insert(parentLine); // link back to head of while loop
                    linkPrevLines(cfg, nodesToJoin, parentLine);
                    nodesToJoin.push_back(parentLine);
                }
                if (!nodesToJoin.empty() && i + 1 < program.size()) {
                    int nextLineNum = program[i + 1].getLineNumber();
                    if(nextLineNum) {
                        linkPrevLines(cfg, nodesToJoin, nextLineNum);
                    }
                }
                justExited = make_pair(parentLine, parentType);
                nestingStack.pop();
            }
            prevLineHasNumber = false;
        } else {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            prevLineHasNumber = true;
        }
        if (lineNumber > 0) prevLineNumber = lineNumber;
        if (lineType != "}") justExited = make_pair(0, "");;
    }

    return cfg;
}

