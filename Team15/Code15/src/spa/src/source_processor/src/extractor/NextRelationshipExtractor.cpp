#include "source_processor/include/extractor/NextRelationshipExtractor.h"

/**
 * To be used to get prevCFGNode when at the end of the if-then/else block and link it to the
 */
void storeLinesToLink(const Line& prevLine, pair<int, string>& justExited, int prevLineNumber, vector<int>& nodesToJoin) {
    if (prevLine.getType() == "}") {
        if (justExited.second == "while") nodesToJoin.push_back(justExited.first);
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
        if (i >= 1 && parentType == "while") {
            linkAllToLine(nodesToJoin, cfg, parentLine);
            return;
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

void linkCallStatements(const unordered_map<string, set<int>>& entryAndExitPointsOfProc,
                        const unordered_map<int, string>& callLineNumToProcName,
                        unordered_map<int, set<int>>& cfg) {
    for (auto[callLine, procName] : callLineNumToProcName) {
        set<int> entryAndExitPoints = entryAndExitPointsOfProc.at(procName);
        for (int i: entryAndExitPoints) {
            cfg[callLine].insert(i);
        }
    }
}

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS,
                                           const unordered_map<int, string>& callLineNumToProcName) {
    unordered_map<int, set<int>> cfg;

    if (program.size() < 2) return cfg;
    unordered_map<string, set<int>> entryAndExitPointsOfProc;
    // intermediate data structures for each procedure
    vector<pair<int, string>> nestingStack;
    vector<int> nodesToJoin;
    bool linkPrevLine = false;
    int prevLineNumber;
    int currMaxLineNumber = 0;
    int nextLineNumber;
    string currProc;
    pair<int, string> justExited;
    for (int i = 0; i < program.size(); i++) {
        Line line = program[i];
        int lineNumber = line.getLineNumber();
        string lineType = line.getType();
        currMaxLineNumber = max(currMaxLineNumber, lineNumber);
        nextLineNumber = currMaxLineNumber + 1;
        bool shouldLinkPrevLine = linkPrevLine && prevLineNumber != lineNumber;
        if (lineType == "procedure") {
            currProc = getProcedureNameFromProcedureStatement(line.getTokens());
            nestingStack.clear();
            nodesToJoin.clear();
            linkPrevLine = false;
            justExited = make_pair(0, "");
            entryAndExitPointsOfProc[currProc].insert(nextLineNumber); // add entry point of proc
            continue;
        } else if (lineType == "if" || lineType == "while") {
            if (shouldLinkPrevLine) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace_back(lineNumber, lineType);
            cfg[lineNumber].insert(nextLineNumber);
            linkPrevLine = false;
        } else if (lineType == "else") {
            auto [parentLine, parentType] = nestingStack.back();
            cfg[parentLine].insert(nextLineNumber);
            storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
            linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
            linkPrevLine = false;
        } else if (lineType == "}") { // when exiting nesting
            if (!nestingStack.empty()) {
                auto [parentLine, parentType] = nestingStack.back();
                if (parentType == "if") {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
                } else if (parentType == "while") {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkAllToLine(nodesToJoin, cfg, parentLine); //link control flow to head of while
                    nodesToJoin.push_back(parentLine);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, cfg);
                }
                justExited = make_pair(parentLine, parentType);
                nestingStack.pop_back();
            } else { //exiting function
                vector<int> temp;
                storeLinesToLink(program[i - 1], justExited, prevLineNumber, temp);
                entryAndExitPointsOfProc[currProc].insert(temp.begin(), temp.end()); // add exit point of proc
            }
            linkPrevLine = false;
        } else {
            if (shouldLinkPrevLine) {
                cfg[prevLineNumber].insert(lineNumber);
            }
            linkPrevLine = true;
        }
        if (lineNumber > 0) prevLineNumber = lineNumber;
        if (lineType != "}") justExited = make_pair(0, "");
    }
    linkCallStatements(entryAndExitPointsOfProc, callLineNumToProcName, cfg);
    return cfg;
}

