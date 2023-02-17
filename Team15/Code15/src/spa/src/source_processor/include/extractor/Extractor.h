#pragma once

#include "CommonExtractorHeader.h"
#include "FollowsRelationshipExtractor.h"
#include "ParentsRelationshipExtractor.h"
#include "ModifiesRelationshipExtractor.h"
#include "AssignsRelationshipExtractor.h"
#include "UsesRelationshipExtractor.h"

class Extractor {
public:
    Extractor();
    void extractEntities(const vector<Line> &program);
    void extract(const vector<Line>& program);
    set<string> getVariables();
    set<string> getConstants();
    set<string> getProcedures();
    unordered_map<string, set<int>> getStatements();
    void extractProcedure(Line line);
    void extractConstants(Line line);
    void extractStatement(Line line);
    void extractVariables(Line line);
    void printEntities();

    map<int, int> getFollowsRS();
    map<int, set<int>> getFollowsStarRS();

    map<int, int> getParentRS();
    map<int, set<int>> getParentStarRS();

    unordered_map<int, set<string>> getModifiesRS();
    unordered_map<int, set<string>> getUsesRS();
    unordered_map<string, set<Line>> getAssignsRS();

private:
    map<int, int> parentsRS;
    map<int, set<int>> parentsStarRS;

    map<int, int> followsRS;
    map<int, set<int>> followsStarRS;

    unordered_map<int, set<string>> modifiesRS;
    unordered_map<int, set<string>> usesRS;
    unordered_map<string, set<Line>> assignsRS;

    set<string> variables;
    set<string> constants;
    set<string> procedures;
    unordered_map<string, set<int>> statements;
};
