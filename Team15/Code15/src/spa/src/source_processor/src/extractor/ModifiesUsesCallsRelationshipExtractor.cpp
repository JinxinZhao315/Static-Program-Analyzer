#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

ModifiesUsesCallsRS extractModifiesUsesAndCallRS(const vector<Line>& program, const set<string>& variables) {
    ModifiesUsesCallsRS result;
    // Intermediate data structures
    vector<int> stmtContainerStack;
    string currProcedure;
    vector<Line> callStatements;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();

        if (lineType == "else" || !currLineNumber) {
            continue;
        } else if (lineType == "procedure") {
            stmtContainerStack.clear(); // new procedure failsafe
            currProcedure = getProcedureNameFromProcedureStatement(tokens);
            continue;
        } else if (lineType == "if" || lineType == "while") { // keep track of stmt container line number
            stmtContainerStack.push_back(currLineNumber);
            continue;
        } else if (lineType == "}") {
            if (!stmtContainerStack.empty()) {
                stmtContainerStack.pop_back();
            }
            continue;
        }

        string LHSVar;
        set<string> RHSVars;
        if (lineType == "=") { // LHS is being modified and RHS is being used
            auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
            LHSVar = LHS[0];
            RHSVars = getVariablesFromStatement(RHS, variables);
        } else if (lineType == "read") { // modifies variable
            LHSVar = getVarNameFromReadStatement(tokens);
        } else if (lineType == "print") { // uses variable
            RHSVars.insert(getVarNameFromPrintStatement(tokens));
        } else if (lineType == "call") { // calls procedure
            result.callsRS[currProcedure].insert(getProcedureNameFromCallStatement(tokens));
        } else if (lineType == "if" || lineType == "while") { // uses variable in conditions
            RHSVars = getVariablesFromStatement(tokens, variables);
        }

        if (!LHSVar.empty()) {
            result.modifiesRS[currLineNumber].insert(LHSVar);
            result.procedureModifiesRS[currProcedure].insert(LHSVar);
            for (auto stmtContainerLine : stmtContainerStack) {
                result.modifiesRS[stmtContainerLine].insert(LHSVar);
            }
        }

        if (!RHSVars.empty()) {
            result.usesRS[currLineNumber].insert(RHSVars.begin(), RHSVars.end());
            result.procedureUsesRS[currProcedure].insert(RHSVars.begin(), RHSVars.end());
            for (auto stmtContainerLine : stmtContainerStack) {
                result.usesRS[stmtContainerLine].insert(RHSVars.begin(), RHSVars.end());
            }
        }

        // determine transitive relationship callsStar
        for (const auto& [caller, callees] : result.callsRS) {
            set<string> visited{caller};
            stack<string> toVisit;
            toVisit.push(caller);

            while (!toVisit.empty()) {
                string curr = toVisit.top();
                toVisit.pop();

                for (const auto& callee : result.callsRS.at(curr)) {
                    if (visited.find(callee) == visited.end()) {
                        visited.insert(callee);
                        toVisit.push(callee);
                        result.callsStarRS[caller].insert(callee);
                    }
                }
            }
        }

    }

    return result;
}

