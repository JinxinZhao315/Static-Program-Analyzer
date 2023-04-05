#include "source_processor/include/extractor/NextRelationshipExtractor.h"

Keywords nextKeywords;

void storeLinesToLink(const Line& prevLine, pair<int, string>& justExited, int prevLineNumber, vector<int>& nodesToJoin) {
    if (prevLine.getType() == CLOSE_CURLY) {
        if (justExited.second == nextKeywords.keywordMap.second.at(WHILE)) nodesToJoin.push_back(justExited.first);
    } else {
        nodesToJoin.push_back(prevLineNumber);
    }
}

void linkAllToLine(vector<int>& nodesToJoin, unordered_map<int, set<int>>& nextRS, int targetLine) {
    for (auto nodeToJoin : nodesToJoin) {
        nextRS[nodeToJoin].insert(targetLine);
    }
    nodesToJoin.clear();
}

void linkStoredLines(vector<int>& nodesToJoin, const vector<pair<int, KeywordsEnum>>& nestingStack,
                     const unordered_map<int, int>& followsRS,
                     unordered_map<int, set<int>>& nextRS) {
    int i = 0;
    for (auto it = nestingStack.rbegin(); it != nestingStack.rend(); ++it) {
        auto parentLine = it->first;
        auto parentType = it->second;
        if (i >= 1 && parentType == WHILE) {
            linkAllToLine(nodesToJoin, nextRS, parentLine);
            nodesToJoin.clear();
            return;
        } else if (followsRS.count(parentLine) > 0) {
            int lineThatFollowsParent = followsRS.at(parentLine);
            linkAllToLine(nodesToJoin, nextRS, lineThatFollowsParent);
            nodesToJoin.clear();
            return;
        }
        i++;
    }
    nodesToJoin.clear();
}

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS) {
    unordered_map<int, set<int>> nextRS;

    if (program.size() < 2) return nextRS;

    // intermediate data structures for each procedure
    vector<pair<int, KeywordsEnum>> nestingStack;
    vector<int> nodesToJoin;
    bool linkPrevLine = false;
    int prevLineNumber;
    int currMaxLineNumber = 0;
    int nextLineNumber;
    pair<int, string> justExited;
    for (int i = 0; i < program.size(); i++) {
        const Line& line = program[i];
        int lineNumber = line.getLineNumber();
        KeywordsEnum lineType = line.getType();
        currMaxLineNumber = max(currMaxLineNumber, lineNumber);
        nextLineNumber = currMaxLineNumber + 1;
        bool shouldLinkPrevLine = linkPrevLine && prevLineNumber != lineNumber;
        if (lineType == PROCEDURE) {
            nestingStack.clear();
            nodesToJoin.clear();
            linkPrevLine = false;
            justExited = make_pair(0, "");
            continue;
        } else if (lineType == IF || lineType == WHILE) {
            if (shouldLinkPrevLine) {
                nextRS[prevLineNumber].insert(lineNumber);
            }
            nestingStack.emplace_back(lineNumber, lineType);
            nextRS[lineNumber].insert(nextLineNumber);
            linkPrevLine = false;
        } else if (lineType == ELSE) {
            auto [parentLine, parentType] = nestingStack.back();
            nextRS[parentLine].insert(nextLineNumber);
            storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
            linkStoredLines(nodesToJoin, nestingStack, followsRS, nextRS);
            linkPrevLine = false;
        } else if (lineType == CLOSE_CURLY) { // when exiting nesting
            if (!nestingStack.empty()) {
                auto [parentLine, parentType] = nestingStack.back();
                if (parentType == IF) {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, nextRS);
                } else if (parentType == WHILE) {
                    storeLinesToLink(program[i - 1], justExited, prevLineNumber, nodesToJoin);
                    linkAllToLine(nodesToJoin, nextRS, parentLine); //link control flow to head of while
                    nodesToJoin.push_back(parentLine);
                    linkStoredLines(nodesToJoin, nestingStack, followsRS, nextRS);
                }
                justExited = make_pair(parentLine, parentType);
                nestingStack.pop_back();
            } else { //exiting function
                vector<int> temp;
                storeLinesToLink(program[i - 1], justExited, prevLineNumber, temp);
            }
            linkPrevLine = false;
        } else {
            if (shouldLinkPrevLine) {
                nextRS[prevLineNumber].insert(lineNumber);
            }
            linkPrevLine = true;
        }
        if (lineNumber > 0) prevLineNumber = lineNumber;
        if (lineType != CLOSE_CURLY) justExited = make_pair(0, "");
    }
    return nextRS;
}

unordered_map<int, set<int>> extractNextStarRS(const unordered_map<int, set<int>>& nextRS) {
    unordered_map<int, set<int>> nextStarRS;
    generateTransitiveRelationship(nextRS, nextStarRS, true);
    return nextStarRS;
}

