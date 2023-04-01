#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

tuple<unordered_map<int, int>, unordered_map<int, set<int>>> extractFollowsRelationship(const vector<Line>& program) {
    vector<int> v;
    unordered_map<int, int> followsRS;
    unordered_map<int, int> parent;
    int prevLineNumber = 0;
    for (const Line& line: program) {
        int currLineNumber = line.getLineNumber();
        KeywordsEnum lineType = line.getType();
        if (lineType == PROCEDURE) {
            // new procedure, store everything in temp and start anew
            parent.clear();
            v.clear();
            prevLineNumber = 0;
            continue;
        }
        // keep track of which block curr line is in
        if (!v.empty() && currLineNumber) {
            parent[currLineNumber] = v.back();
        }
        // if they share the same parent, and consecutive lines
        bool bothNoParent = (parent.find(prevLineNumber) == parent.end()) && (parent.find(currLineNumber) == parent.end());
        bool bothSameParent = parent[prevLineNumber] == parent[currLineNumber];
        bool isSiblings = bothNoParent || bothSameParent;
        if (prevLineNumber && currLineNumber && isSiblings) {
            followsRS[prevLineNumber] = currLineNumber;
        }
        if (lineType == IF || lineType == WHILE) {
            v.push_back(currLineNumber);
        } else if (lineType == ELSE) {
            if (!v.empty()) {
                int elseParentValue = -1 * v.back();
                v.pop_back();
                v.push_back(elseParentValue);
            }
        } else if (lineType == CLOSE_CURLY) {
            if (!v.empty()) {
                prevLineNumber = abs(v.back()); //parent may be negative if it was an else block
                v.pop_back(); // jump out of a block
                continue;
            }
        }
        if (currLineNumber) {
            prevLineNumber = currLineNumber;
        }
    }
    unordered_map<int, set<int>> followsStarRS;
    generateTransitiveRelationship(followsRS, followsStarRS);
    return make_tuple(followsRS, followsStarRS);
}