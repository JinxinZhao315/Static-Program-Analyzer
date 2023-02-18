#include "source_processor/include/extractor/FollowsRelationshipExtractor.h"

tuple<unordered_map<int, int>, unordered_map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program) {
    vector<int> stack;
    unordered_map<int, int> startOfBlockRS;

    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        string lineType = line.getType();

        // start of block logic
        if (lineType == "procedure") stack.clear(); // new procedure - failsafe, might not be needed
        if (lineType == "else") continue;

        if (!stack.empty()) {
                startOfBlockRS[currLineNumber] = stack.back(); // this line belongs to the same nesting level as prev line
        }
        if (lineType == "if" || lineType == "while" || lineType == "else") { //start of new block
            // store previous start of block
            stack.push_back(currLineNumber); // store this before going into new block
        } else if (lineType == "}") { //exiting current block
            if (!stack.empty()) {
                stack.pop_back();
            }
        }
    }

    unordered_map<int, int> followsRS;
    unordered_map<int, set<int> > followsStarRS;
    for (int i = 0; i < program.size(); i++) {
        Line firstLine = program[i];
        int firstLineNumber = firstLine.getLineNumber();
        for (int j = i + 1; j < program.size() - 1; j++) {
            Line secondLine = program[j];
            int secondLineNumber = secondLine.getLineNumber();

            bool isSameBlock = startOfBlockRS[firstLineNumber] == startOfBlockRS[secondLineNumber];
            bool isLineAfter = firstLineNumber + 1 == secondLineNumber;
            if (isLineAfter && isSameBlock) followsRS[firstLineNumber] = secondLineNumber;
            if (isSameBlock) followsStarRS[firstLineNumber].insert(secondLineNumber);
        }
    }
    return make_tuple(followsRS, followsStarRS);
}
