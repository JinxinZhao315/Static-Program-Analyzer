#pragma once

#include "CommonExtractorHeader.h"
#include "NextRelationshipExtractor.h"

//unordered_map<int, set<int>> extractAffectsRS(const vector<Line>& program, const unordered_map<int, int>& followsRS,
//                                              const unordered_map<int, string>& callLineNumToProcName);


// given two statement numbers, check affects(s1, s2)
set<string> extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                              unordered_map<int, set<int>> cfg,
                                              const set<string>& variables,
                                              const unordered_map<int, set<string>>& modifiesRS,
                                              const unordered_map<int, set<string>>& usesRS
                                              );

// find a path between line1 and line2, if found return as vector of ints representing that control flow
void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths);

// unordered_map<int, set<int>> extractAffectsRS