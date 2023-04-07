#include "source_processor/include/extractor/ModifiesUsesCallsRelationshipExtractor.h"

ModifiesUsesCallsRS extractModifiesUsesAndCallRS(const vector<Line>& program, const set<string>& variables) {
    ModifiesUsesCallsRS result;
    // Intermediate data structures
    vector<int> stmtContainerStack;
    string currProcedure;
    vector<Line> callStatements;
    unordered_map<int, string> callToProcName;
    // used to update call stmt containers for modifies and uses
    unordered_map<int, vector<int>> callToStmtContainerStack;
    for (Line line: program) {
        int currLineNumber = line.getLineNumber();
        vector<string> tokens = line.getTokens();
        KeywordsEnum lineType = line.getType();

        if (lineType == PROCEDURE) {
            stmtContainerStack.clear(); // new procedure failsafe
            currProcedure = getProcedureNameFromProcedureStatement(tokens);
            continue;
        } else if (lineType == IF || lineType == WHILE) { // keep track of stmt container line number
            stmtContainerStack.push_back(currLineNumber);
        } else if (lineType == CLOSE_CURLY) {
            if (!stmtContainerStack.empty()) {
                stmtContainerStack.pop_back();
            }
            continue;
        } else if (lineType == ELSE || !currLineNumber) {
            continue;
        }
        string modifiesVars;
        set<string> usesVars;
        if (lineType == ASSIGN) { // LHS is being modified and RHS is being used
            auto [LHS, RHS] = getLHSandRHSofAssignStatement(tokens);
            modifiesVars = LHS[0];
            usesVars = getVariablesFromStatement(RHS, variables);
        } else if (lineType == READ) { // modifies variable
            modifiesVars = getVarNameFromReadStatement(tokens);
        } else if (lineType == PRINT) { // uses variable
            usesVars.insert(getVarNameFromPrintStatement(tokens));
        } else if (lineType == CALL) { // calls procedure
            string procName = getProcedureNameFromCallStatement(tokens);
            result.callsRS[currProcedure].insert(procName);
            callToProcName[currLineNumber] = procName;
            callToStmtContainerStack[currLineNumber] = vector<int>(stmtContainerStack);
        } else if (lineType == IF || lineType == WHILE) { // uses variable in conditions
            usesVars = getVariablesFromStatement(tokens, variables);
        }

        if (!modifiesVars.empty()) {
            result.modifiesRS[currLineNumber].insert(modifiesVars);
            result.procedureModifiesRS[currProcedure].insert(modifiesVars);
            for (auto stmtContainerLine : stmtContainerStack) {
                result.modifiesRS[stmtContainerLine].insert(modifiesVars);
            }
        }

        if (!usesVars.empty()) {
            result.usesRS[currLineNumber].insert(usesVars.begin(), usesVars.end());
            result.procedureUsesRS[currProcedure].insert(usesVars.begin(), usesVars.end());
            for (auto stmtContainerLine : stmtContainerStack) {
                result.usesRS[stmtContainerLine].insert(usesVars.begin(), usesVars.end());
            }
        }
    }
    // determine transitive relationship callsStar
    generateTransitiveRelationship(result.callsRS, result.callsStarRS, false);
    // determine transitive modification of variables through procedure calls
    updateProcModifiesAndUsesRS(result.procedureModifiesRS, result.procedureUsesRS, result.callsStarRS);
    updateCallStmtModifiesAndUsesRS(result.procedureModifiesRS, result.procedureUsesRS, result.modifiesRS, result.usesRS, callToProcName, callToStmtContainerStack);
    return result;
}

void updateProcModifiesAndUsesRS(unordered_map<string, set<string>>& procedureModifiesRS,
                                 unordered_map<string, set<string>>& procedureUsesRS,
                                 unordered_map<string, set<string>>& callsStarRS) {
    for (const auto &[caller, callees]: callsStarRS) {
        for (auto const &callee: callees) {
            // if procedure A has calls to B, procedure A then modifies same variables as B
            if (procedureModifiesRS.count(callee) > 0) {
                set<string> additionalModifies = procedureModifiesRS[callee];
                procedureModifiesRS[caller].insert(additionalModifies.begin(), additionalModifies.end());
            }
            // if procedure A has calls to B, procedure A then uses same variables as B
            if (procedureUsesRS.count(callee) > 0) {
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
                                     const unordered_map<int, string>& callToProcName,
                                     const unordered_map<int, vector<int>>& callToStmtContainerStack) {
    for (const auto& entry : callToProcName) {
        int statementNumber = entry.first;
        string procName = entry.second;
        // if call stmt calls proc A and proc A uses var, then proc A uses same var
        vector<int> stmtContainerStack = callToStmtContainerStack.at(statementNumber);
        if (procedureModifiesRS.count(procName) > 0) {
            set<string> additionalModifies = procedureModifiesRS[procName];
            modifiesRS[statementNumber].insert(additionalModifies.begin(), additionalModifies.end());
            for (auto stmtContainerLine : stmtContainerStack) {
                modifiesRS[stmtContainerLine].insert(additionalModifies.begin(), additionalModifies.end());
            }
        }
        // if call stmt calls proc A and proc A modifies var, then proc A modifies same var
        if (procedureUsesRS.count(procName) > 0) {
            set<string> additionalUses = procedureUsesRS[procName];
            usesRS[statementNumber].insert(additionalUses.begin(), additionalUses.end());
            for (auto stmtContainerLine : stmtContainerStack) {
                usesRS[stmtContainerLine].insert(additionalUses.begin(), additionalUses.end());
            }
        }
    }
}

