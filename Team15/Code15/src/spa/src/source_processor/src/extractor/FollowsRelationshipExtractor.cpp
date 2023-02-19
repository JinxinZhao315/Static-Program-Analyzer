#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

tuple<unordered_map<int, int>, unordered_map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program) {
    vector<int> v;
    unordered_map<int, int> followsRS;
    unordered_map<int, int> parent;
    int prevLineNumber = 0;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        string lineType = line.getType();
        if (lineType == "procedure") {
            // new procedure, store everything in temp and start anew
            parent.clear();
            v.clear();
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
        if (lineType == "if" || lineType == "while") {
            v.push_back(currLineNumber);
        } else if (lineType == "else") {
            if (!v.empty()) {
                int elseParentValue = -1 * v.back();
                v.pop_back();
                v.push_back(elseParentValue);
            }
        } else if (lineType == "}") {
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
    // store info for last procedure
    unordered_map<int, set<int>> followsStarRS;
    for (const auto& p : followsRS) {
        int leader = p.first;
        int follower = p.second;

        if (followsStarRS.count(leader) == 0) {
            followsStarRS[leader] = {follower};
        } else {
            followsStarRS[leader].insert(follower);
        }

        // Check transitive relationships for followers
        while (followsRS.count(follower)) {
            follower = followsRS[follower];
            followsStarRS[leader].insert(follower);
        }
    }
    return make_tuple(followsRS, followsStarRS);
}