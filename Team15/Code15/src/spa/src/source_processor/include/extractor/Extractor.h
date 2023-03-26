#pragma once

#include "CommonExtractorHeader.h"
#include "FollowsRelationshipExtractor.h"
#include "ParentsRelationshipExtractor.h"
#include "ModifiesUsesCallsRelationshipExtractor.h"
#include "AssignsRelationshipExtractor.h"
#include "ConditionalRelationshipExtractor.h"
#include "ConstantExtractor.h"
#include "ProcedureExtractor.h"
#include "VariableExtractor.h"
#include "StatementExtractor.h"
#include "NextRelationshipExtractor.h"

class Extractor {
public:
    Extractor();
    void extract(const vector<Line>& program);
    set<string> getVariables();
    set<string> getConstants();
    set<string> getProcedures();
    unordered_map<string, set<int>> getStatements();
    void printEntities();

    unordered_map<int, int> getFollowsRS();
    unordered_map<int, set<int>> getFollowsStarRS();

    unordered_map<int, set<int>> getParentRS();
    unordered_map<int, set<int>> getParentStarRS();

    unordered_map<string, set<Line>> getAssignsRS();
    unordered_map<string, set<Line>> getIfRS();
    unordered_map<string, set<Line>> getWhileRS();

    unordered_map<int, set<string>> getModifiesRS();
    unordered_map<string, set<string>> getProcedureModifiesRS();

    unordered_map<int, set<string>> getUsesRS();
    unordered_map<string, set<string>> getProcedureUsesRS();

    unordered_map<string, set<string>> getCallsRS();
    unordered_map<string, set<string>> getCallsStarRS();

    unordered_map<int, string> getReadLineNumToVarName();
    unordered_map<int, string> getPrintLineNumToVarName();
    unordered_map<int, string> getCallLineNumToProcName();

    unordered_map<int, set<int>> getNextRS();

private:
    unordered_map<int, set<int>> parentsRS;
    unordered_map<int, set<int>> parentsStarRS;

    unordered_map<int, int> followsRS;
    unordered_map<int, set<int>> followsStarRS;

    unordered_map<string, set<string>> procedureModifiesRS;
    unordered_map<string, set<string>> procedureUsesRS;

    unordered_map<string, set<string>> callsRS;
    unordered_map<string, set<string>> callsStarRS;

    unordered_map<int, set<string>> modifiesRS;
    unordered_map<int, set<string>> usesRS;

    unordered_map<string, set<Line>> assignsRS;
    unordered_map<string, set<Line>> ifRS;
    unordered_map<string, set<Line>> whileRS;

    set<string> procedures;
    set<string> constants;
    set<string> variables;
    unordered_map<string, set<int>> statements;

    unordered_map<int, string> readLineNumToVarName;
    unordered_map<int, string> printLineNumToVarName;
    unordered_map<int, string> callLineNumToProcName;

    unordered_map<int, set<int>> nextRS;

    VariableExtractor* variableExtractor;
    ProcedureExtractor* procedureExtractor;
};
