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
    vector<string> getConstants();
    set<string> getProcedures();
    map<string, vector<int>> getStatements();
    void extractProcedure(Line line);
    void extractConstants(Line line);
    void extractStatement(Line line);
    void extractVariables(Line line);
    void printEntities();

private:
    map<int, int> parentsRS;
    map<int, set<int> > parentsStarRS;

    map<int, int> followsRS;
    map<int, set<int> > followsStarRS;

    set<string> variables;
    vector<string> constants;
    set<string> procedures;
    map<string, vector<int>> statements;
};
