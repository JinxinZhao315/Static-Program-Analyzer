#pragma once

#include <utility>
#include "CommonExtractorHeader.h"
#include "NextRelationshipExtractor.h"

// given two statement numbers, check affects(s1, s2)
bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                              const unordered_map<int, set<int>>& cfg,
                                              const set<string>& variables,
                                              const unordered_map<int, set<string>>& modifiesRS,
                                              const unordered_map<int, set<string>>& usesRS,
                                              bool findAffectsStar
                                              );

// find a path between line1 and line2, if found return as vector of ints representing that control flow
void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths,
         unordered_map<int, int>* visited);
