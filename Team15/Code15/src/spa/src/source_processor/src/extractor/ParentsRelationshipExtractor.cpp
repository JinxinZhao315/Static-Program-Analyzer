#include "source_processor/include/extractor/ParentsRelationshipExtractor.h"

tuple<unordered_map<int, set<int>>, unordered_map<int, set<int> >> extractParentsRelationship(const vector<Line>& program) {
    vector<int> v;
    unordered_map<int, set<int>> parentsRS;
    unordered_map<int, int> parent;
    for (const Line& line: program) {
        int currLineNumber = line.getLineNumber();
        KeywordsEnum lineType = line.getType();
        if (lineType == PROCEDURE) {
            v.clear();
            continue;
        }
        // keep track of which block curr line is in
        if (!v.empty() && currLineNumber) {
            parent[currLineNumber] = v.back();
            parentsRS[v.back()].insert(currLineNumber);
        }
        if (lineType == IF || lineType == WHILE) {
            v.push_back(currLineNumber);
        } else if (lineType == ELSE) {
            continue;
        } else if (lineType == CLOSE_CURLY) {
            if (!v.empty()) {
                v.pop_back(); // jump out of a block
                continue;
            }
        }
    }
    // store info for last procedure
    unordered_map<int, set<int>> parentsStarRS;
    generateTransitiveRelationship(parentsRS, parentsStarRS);

    return make_tuple(parentsRS, parentsStarRS);
}