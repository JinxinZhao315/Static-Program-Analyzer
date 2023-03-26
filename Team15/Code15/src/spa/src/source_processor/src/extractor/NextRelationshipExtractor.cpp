#include "source_processor/include/extractor/NextRelationshipExtractor.h"

/**
 * To be used to get prevCFGNode when at the end of the if-then/else block and link it to the
 */
void storeLinesToLink(const Line& prevLine, pair<int, string>& justExited, const int& prevLineNumber, vector<int>& nodesToJoin) {
    if (prevLine.getType() == "}") {
        auto [parentLine, parentType] = justExited;
        if (parentType == "while") {
            nodesToJoin.push_back(parentLine);
        }
    } else {
        nodesToJoin.push_back(prevLineNumber);
    }
}
void linkAllToLine(vector<int>& nodesToJoin, unordered_map<int, set<int>>& cfg, int targetLine) {
    for (auto nodeToJoin : nodesToJoin) {
        cfg[nodeToJoin].insert(targetLine);
    }
    nodesToJoin.clear();
}

void linkStoredLines(vector<int>& nodesToJoin, const vector<pair<int, string>>& nestingStack, const unordered_map<int, int>& followsRS,  unordered_map<int, set<int>>& cfg) {
    int i = 0;
    for (auto it = nestingStack.rbegin(); it != nestingStack.rend(); ++it) {
        auto parentLine = it->first;
        auto parentType = it->second;
        if (i >= 1) {
            if (parentType == "while") {
                linkAllToLine(nodesToJoin, cfg, parentLine);
                return;
            }
        }
        if (followsRS.count(parentLine) > 0) {
            int lineThatFollowsParent = followsRS.at(parentLine);
            linkAllToLine(nodesToJoin, cfg, lineThatFollowsParent);
            return;
        }
        i++;
    }
    nodesToJoin.clear();
}



unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) {
        return cfg;
    }
    // intermediate data structures for each procedure
    vector<pair<int, string>> nestingStack;
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
            nestingStack = vector<pair<int, string>>(); // clear stack
            nodesToJoin.clear();
            prevLineHasNumber = false;
            justExited = make_pair(0, "");;
            continue;
        } else if (lineType == "if" || lineType == "while") {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace_back(lineNumber, lineType);
            cfg[lineNumber].insert(nextLineNumber);
            prevLineHasNumber = false;
        } else if (lineType == "else") {
            auto [parentLine, parentType] = nestingStack.back();
            cfg[parentLine].insert(nextLineNumber);
            storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
            linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
            prevLineHasNumber = false;
        } else if (lineType == "}") { // when exiting nesting
            if (!nestingStack.empty()) {
                auto [parentLine, parentType] = nestingStack.back();
                if (parentType == "if") {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
                } else if (parentType == "while") {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkAllToLine(nodesToJoin, cfg, parentLine);
                    nodesToJoin.push_back(parentLine);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
                }
                justExited = make_pair(parentLine, parentType);
                nestingStack.pop_back();
            }
            prevLineHasNumber = false;
        } else {
            if (isPrevLineValid) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            prevLineHasNumber = true;
        }
        if (lineNumber > 0) prevLineNumber = lineNumber;
        if (lineType != "}") justExited = make_pair(0, "");
    }

    return cfg;
}

