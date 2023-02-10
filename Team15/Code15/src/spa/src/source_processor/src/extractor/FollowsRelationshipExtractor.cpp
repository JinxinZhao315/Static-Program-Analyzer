#include "../../include/extractor/FollowsRelationshipExtractor.h"

tuple<map<int, int>, map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program, const map<int, int>& parentsRS) {
    map<int, int> nestingLevel;
    int currNestingLevel;

    int startOfBlock = 0;
    stack<int> stack;
    map<int, int> startOfBlockRS;

    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        string lineType = line.getType();

        // nesting logic
        if (lineType == "if" || lineType == "while") {
            nestingLevel[currLineNumber] = currNestingLevel++; //increment after assigning
        } else if (lineType == "}") { // this type of line has no line number
            currNestingLevel--; //decrement before assigning
        } else {
            nestingLevel[currLineNumber] = currNestingLevel;
        }

        // start of block logic
        if (lineType == "if" || lineType == "while" || lineType == "else") { //start of new block
            // store previous start of block
            startOfBlockRS[currLineNumber] = startOfBlock; // this line belongs to the same nesting level as prev line
            stack.push(startOfBlock); // store this before going into new block
            startOfBlock = currLineNumber; // now this line is the start of a new block
        } else if (lineType == "}") { //exiting current block
            startOfBlock = stack.top();
            stack.pop();
        } else {
            startOfBlockRS[currLineNumber] = startOfBlock;
        }
    }

    map<int, int> followsRS;
    map<int, set<int> > followsStarRS;

    for (auto outer_it = nestingLevel.begin(); outer_it != nestingLevel.end(); ++outer_it) {
        for (auto inner_it = next(outer_it); inner_it != nestingLevel.end(); ++inner_it) {
            int firstLine = outer_it->first;
            int secondLine = inner_it->first;
            int firstNesting = outer_it->second;
            int secondNesting = inner_it->second;
            bool isSameNesting = firstNesting == secondNesting;
            bool isSameBlock = startOfBlockRS[firstLine] == startOfBlock[secondLine];
            if (isSameNesting && isSameBlock) {
                followsRS[firstLine] = secondLine;
            }
        }
    }


    return tuple(followsRS, followsStarRS)
}
