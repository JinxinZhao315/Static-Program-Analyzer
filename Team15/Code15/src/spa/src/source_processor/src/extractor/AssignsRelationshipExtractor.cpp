#include "source_processor/include/extractor/AssignsRelationshipExtractor.h"

unordered_map<string, set<Line>> extractAssignmentRS(const vector<Line>& program, const set<string>& variables) {
    unordered_map<string, set<Line>> assignsRS;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();
        if (lineType != "=") continue;
        auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
        string varName = LHS[0];
        vector<string> postfixRHS = convertToPostfix(RHS, variables);
        Line newLine(currLineNumber, postfixRHS);
        if (assignsRS.count(varName) == 0) {
            assignsRS.emplace(varName, set<Line>({newLine}));
        } else {
            assignsRS[varName].insert(newLine);
        }
    }
    return assignsRS;
}