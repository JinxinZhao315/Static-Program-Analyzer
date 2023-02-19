#pragma once

#include "CommonExtractorHeader.h"
#include "FollowsRelationshipExtractor.h"
#include "ParentsRelationshipExtractor.h"
#include "ModifiesRelationshipExtractor.h"
#include "AssignsRelationshipExtractor.h"
#include "UsesRelationshipExtractor.h"
#include "ConstantExtractor.h"
#include "ProcedureExtractor.h"
#include "VariableExtractor.h"
#include "StatementExtractor.h"

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

    unordered_map<int, set<string>> getModifiesRS();
    unordered_map<int, set<string>> getUsesRS();
    unordered_map<string, set<Line>> getAssignsRS();


private:
    unordered_map<int, set<int>> parentsRS;
    unordered_map<int, set<int>> parentsStarRS;

    unordered_map<int, int> followsRS;
    unordered_map<int, set<int>> followsStarRS;

    unordered_map<int, set<string>> modifiesRS;
    unordered_map<int, set<string>> usesRS;
    unordered_map<string, set<Line>> assignsRS;

    set<string> procedures;
    set<string> constants;
    set<string> variables;
    unordered_map<string, set<int>> statements;
};
