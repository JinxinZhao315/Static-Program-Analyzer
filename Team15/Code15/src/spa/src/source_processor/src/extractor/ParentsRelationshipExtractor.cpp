#include "../../include/extractor/ParentsRelationshipExtractor.h"

tuple<map<int, int>, map<int, set<int> >> extractParentsRelationship(const vector<Line>& program) {
    map<int, int> parentsRS;
    map<int, set<int> > parentsStarRS;
    vector<int> parentStack;

    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();
        if (lineType == "else") continue;
        if (lineType == "procedure") parentStack.clear(); // new procedure - failsafe, might not be needed
        // Store parents relationship
        if (!parentStack.empty()) { // has parent
            int parent = parentStack.back();
            parentsRS[parent] = currLineNumber;
        }
        // Store parents* relationship
        set<int> ancestorsSet(parentStack.begin(), parentStack.end());
        parentsStarRS[currLineNumber] = ancestorsSet;

        if (lineType == "if" || lineType == "while") {
            parentStack.push_back(currLineNumber);
            parentsRS[currLineNumber] = currLineNumber;
        } else if (lineType == "}") {
            if (!parentStack.empty()) {
                parentStack.pop_back();
            }
        }
    }
    return tuple(parentsRS, parentsStarRS);
}