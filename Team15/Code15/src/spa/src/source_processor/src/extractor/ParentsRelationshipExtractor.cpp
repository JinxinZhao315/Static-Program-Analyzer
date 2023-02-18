#include "source_processor/include/extractor/ParentsRelationshipExtractor.h"

tuple<unordered_map<int, set<int>>, unordered_map<int, set<int> >> extractParentsRelationship(const vector<Line>& program) {
    vector<int> v;
    unordered_map<int, set<int>> parentsRS;
    unordered_map<int, int> parent;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        string lineType = line.getType();
        if (lineType == "procedure") {
//            parent.clear();
            continue;
        }
        // keep track of which block curr line is in
        if (!v.empty() && currLineNumber) {
            parent[currLineNumber] = v.back();
            parentsRS[v.back()].insert(currLineNumber);
        }
        if (lineType == "if" || lineType == "while") {
            v.push_back(currLineNumber);
        } else if (lineType == "else") {
            continue;
        } else if (lineType == "}") {
            if (!v.empty()) {
                v.pop_back(); // jump out of a block
                continue;
            }
        }
    }
    // store info for last procedure
//    parentsRS = unordered_map<int, int>(tempParents.begin(), tempParents.end());
    unordered_map<int, set<int>> parentsStarRS;
    for (const auto& p : parent) {
        int child = p.first;
        int parentLine = p.second;

        while (parentLine) {
            // Initialize set for parent if it does not exist
            parentsStarRS[parentLine].insert(child);

            // Check if there is a transitive relationship
            if (parent.count(parentLine)) {
                parentLine = parent.at(parentLine);
            } else {
                parentLine = 0;
            }
        }
    }

    return make_tuple(parentsRS, parentsStarRS);
}