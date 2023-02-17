#include "source_processor/include/extractor/ParentsRelationshipExtractor.h"

tuple<unordered_map<int, int>, unordered_map<int, set<int> >> extractParentsRelationship(const vector<Line>& program) {
    unordered_map<int, int> parentsRS;
    unordered_map<int, set<int> > parentsStarRS;
    vector<int> parentStack;

    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        string lineType = line.getType();
        if (lineType == "else") continue;
        if (lineType == "procedure") parentStack.clear(); // new procedure - failsafe, might not be needed
        // Store parents relationship
        if (!parentStack.empty()) { // has parent
            int parent = parentStack.back();
            parentsRS.emplace(parent, currLineNumber);
        }
        // Store parents* relationship
        const set<int> ancestorsSet{parentStack.begin(), parentStack.end()};
        parentsStarRS.emplace(currLineNumber, ancestorsSet);

        if (lineType == "if" || lineType == "while") {
            parentStack.push_back(currLineNumber);
            parentsRS.emplace(currLineNumber, currLineNumber);
        } else if (lineType == "}") {
            if (!parentStack.empty()) {
                parentStack.pop_back();
            }
        }
    }
    return make_tuple(parentsRS, parentsStarRS);
}