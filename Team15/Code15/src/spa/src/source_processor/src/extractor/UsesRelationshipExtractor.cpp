#include "source_processor/include/extractor/UsesRelationshipExtractor.h"

/**
 * Goes through each line of the program and checks if the line is a read, assign or is a container where modifies holds
 */
unordered_map<int, set<string>> extractUsesRS(const vector<Line>& program, const set<string>& variables) {
    unordered_map<int, set<string>> usesRS;
    vector<int> stmtContainerStack;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();

        if (lineType == "call" || lineType == "else") {
            continue;
        } else if (lineType == "procedure") {
            stmtContainerStack.clear(); // new procedure failsafe
            continue;
        } else if (lineType == "if" || lineType == "while") { // keep track of stmt container line number
            stmtContainerStack.push_back(currLineNumber);
        } else if (lineType == "}") {
            if (!stmtContainerStack.empty()) {
                stmtContainerStack.pop_back();
            }
        }

        set<string> varNames;
        if (lineType == "=") {
            auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
            varNames = getVariablesFromStatement(RHS, variables);
        } else if (lineType == "print") {
            varNames.insert(getVarNameFromPrintStatement(tokens));
        } else if (lineType == "if" || lineType == "while") {
            varNames = getVariablesFromStatement(tokens, variables);
        }
        if (currLineNumber && !varNames.empty()) {
            usesRS[currLineNumber].insert(varNames.begin(), varNames.end()); // for current line
        }
        if (!stmtContainerStack.empty()) { // for stmtContainer: modifies(s, v)
            for (auto stmtContainerLine : stmtContainerStack) {
                usesRS[stmtContainerLine].insert(varNames.begin(), varNames.end());
            }
        }
    }
    return usesRS;
}