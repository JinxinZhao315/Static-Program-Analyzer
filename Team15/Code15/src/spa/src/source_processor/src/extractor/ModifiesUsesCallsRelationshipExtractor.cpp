#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

ModifiesUsesCallsRS extractModifiesUsesAndCallRS(const vector<Line>& program, const set<string>& variables) {
    ModifiesUsesCallsRS result;
    // Intermediate data structures
    vector<int> stmtContainerStack;
    string currProcedure;
    vector<Line> callStatements;
    unordered_map<int, string> callToProcName;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        string lineType = line.getType();

        if (lineType == "procedure") {
            stmtContainerStack.clear(); // new procedure failsafe
            currProcedure = getProcedureNameFromProcedureStatement(tokens);
            continue;
        } else if (lineType == "if" || lineType == "while") { // keep track of stmt container line number
            stmtContainerStack.push_back(currLineNumber);
        } else if (lineType == "}") {
            if (!stmtContainerStack.empty()) {
                stmtContainerStack.pop_back();
            }
            continue;
        } else if (lineType == "else" || !currLineNumber) {
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
            string procName = getProcedureNameFromCallStatement(tokens);
            result.callsRS[currProcedure].insert(procName);
            callToProcName[currLineNumber] = procName;
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
    }
    // determine transitive relationship callsStar
    generateCallsStarRS(result.callsRS, result.callsStarRS);
    // determine transitive modification of variables through procedure calls
    updateProcModifiesAndUsesRS(result.procedureModifiesRS, result.procedureUsesRS, result.callsStarRS);
    updateCallStmtModifiesAndUsesRS(result.procedureModifiesRS, result.procedureUsesRS, result.modifiesRS, result.usesRS, callToProcName);
    return result;
}

void generateCallsStarRS(unordered_map<string, set<string>>& callsRS, unordered_map<string, set<string>>& callsStarRS) {
    for (const auto& [caller, callees] : callsRS) {
        set<string> visited{caller};
        stack<string> toVisit;
        toVisit.push(caller);

        while (!toVisit.empty()) {
            string curr = toVisit.top();
            toVisit.pop();

            auto it = callsRS.find(curr);
            if (it != callsRS.end()) {
                for (const auto& callee : it->second) {
                    if (visited.find(callee) == visited.end()) {
                        visited.insert(callee);
                        toVisit.push(callee);
                        callsStarRS[caller].insert(callee);
                    }
                }
            }
        }
    }
}

void updateProcModifiesAndUsesRS(unordered_map<string, set<string>>& procedureModifiesRS,
                                 unordered_map<string, set<string>>& procedureUsesRS,
                                 unordered_map<string, set<string>>& callsStarRS) {
    for (const auto &[caller, callees]: callsStarRS) {
        for (auto const &callee: callees) {
            // if procedure A has calls to B, procedure A then modifies same variables as B
            if (procedureModifiesRS.find(callee) != procedureModifiesRS.end()) {
                set<string> additionalModifies = procedureModifiesRS[callee];
                procedureModifiesRS[caller].insert(additionalModifies.begin(), additionalModifies.end());
            }
            // if procedure A has calls to B, procedure A then uses same variables as B
            if (procedureUsesRS.find(callee) != procedureUsesRS.end()) {
                set<string> additionalUses = procedureUsesRS[callee];
                procedureUsesRS[caller].insert(additionalUses.begin(), additionalUses.end());
            }
        }
    }
}
void updateCallStmtModifiesAndUsesRS(unordered_map<string, set<string>>& procedureModifiesRS,
                                     unordered_map<string, set<string>>& procedureUsesRS,
                                     unordered_map<int, set<string>>& modifiesRS,
                                     unordered_map<int, set<string>>& usesRS,
                                     const unordered_map<int, string>& callToProcName) {
    for (const auto& entry : callToProcName) {
        int statementNumber = entry.first;
        string procName = entry.second;
        // if call stmt calls proc A and proc A uses var, then proc A uses same var
        if (procedureModifiesRS.find(procName) != procedureModifiesRS.end()) {
            set<string> additionalModifies = procedureModifiesRS[procName];
            modifiesRS[statementNumber].insert(additionalModifies.begin(), additionalModifies.end());
        }
        // if call stmt calls proc A and proc A modifies var, then proc A modifies same var
        if (procedureUsesRS.find(procName) != procedureUsesRS.end()) {
            set<string> additionalUses = procedureUsesRS[procName];
            usesRS[statementNumber].insert(additionalUses.begin(), additionalUses.end());
        }
    }
}

