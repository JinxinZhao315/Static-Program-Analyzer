#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <stack>
#include <stdio.h>
#include <iostream>
#include <utility>
#include "../parser/Line.h"
#include "FollowsRelationshipExtractor.h"
#include "ParentsRelationshipExtractor.h"

using namespace std;

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
