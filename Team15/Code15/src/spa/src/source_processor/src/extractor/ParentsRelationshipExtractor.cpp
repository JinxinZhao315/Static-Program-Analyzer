#include "../../include/extractor/ParentsRelationshipExtractor.h"

bool endsWith(const vector<string>& vec, const string& str) {
    return !vec.empty() && vec.back() == str;
}

pair<map<int, int>, map<int, set<int> > > generateParentsRelationship(const vector<Line>& program) {
    map<int, int> parentsRS;
    map<int, set<int> > parentsStarRS;
    vector<int> parentStack;

    for (Line line: program) { //TODO: iterate through procedures instead of program
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        if (currLineNumber < 0) continue; // no line number - procedure or else block //TODO: check by type of line
        // Store parents relationship
        if (!parentStack.empty()) { // has parent
            int parent = parentStack.back();
            parentsRS[parent, currLineNumber];
        }
        // Store parents* relationship
        set<int> ancestorsSet(parentStack.begin(), parentStack.end());
        parentsStarRS[currLineNumber] = ancestorsSet;


        if (endsWith(tokens, "{")) { //TODO: check by type of line instead of ending char
            parentStack.push_back(currLineNumber); // to keep track of nesting level
        }
    }
    return make_pair(parentsRS, parentsStarRS);
}