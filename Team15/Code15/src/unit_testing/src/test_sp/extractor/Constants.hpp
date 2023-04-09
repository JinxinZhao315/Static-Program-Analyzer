#pragma once
#include "sp/include/extractor/CommonExtractorHeader.h"
#include "catch.hpp"

extern const vector<Line> mainProgram;
extern const vector<Line> whileLoop;
extern const vector<Line> whileLoop2;
extern const vector<Line> computeCentroid;
extern const vector<Line> ifElse;
extern const vector<Line> ifElse2;
extern const vector<Line> ifElseInProcedure;
extern const vector<Line> program;
extern const vector<Line> superNested;
extern const vector<Line> readPoint;
extern const vector<Line> singleAssignmentSelfIncrement;
extern const vector<Line> singleAssignmentAddVariable;
extern const vector<Line> onlyCallStatements;
extern const vector<Line> source2;
extern const vector<Line> source4;
extern const vector<Line> whileLoopInProcedure;
extern const vector<Line> whileLoopInProcedureWithLinesBeforeAfter;

extern const vector<Line> source6;
extern const set<string> mainProgramVariables;
extern const set<string> whileLoopVariables;
extern const set<string> whileLoop2Variables;
extern const set<string> computeCentroidVariables;
extern const set<string> ifElseVariables;
extern const set<string> ifElse2Variables;
extern const set<string> programVariables;
extern const set<string> superNestedVariables;
extern const set<string> readPointVariables;
extern const set<string> singleAssignmentSelfIncrementVariables;
extern const set<string> singleAssignmentAddVariableVariables;
extern const set<string> onlyCallStatementsVariables;
extern const set<string> source2Variables;
extern const set<string> source4Variables;
extern const set<string> source6Variables;

extern void printNodes(const unordered_map<int, set<int>>& myMap);
extern void compareCFG(const unordered_map<int, set<int>>& result, const unordered_map<int, set<int>>& expected);