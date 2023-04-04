#pragma once

#include <utility>
#include "CommonExtractorHeader.h"
#include "NextRelationshipExtractor.h"

bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                              const unordered_map<int, set<int>>& cfg,
                                              const set<string>& variables,
                                              const unordered_map<int, set<string>>& modifiesRS,
                                              const unordered_map<int, set<string>>& usesRS,
                                              bool findAffectsStar
                                              );

set<int> extractAffectsWithWildcard(const vector<Line>& program, int lineNum, bool wildCardIsFirstArg,
                                    const unordered_map<int, set<int>>& cfg,
                                    const set<string>& variables,
                                    const unordered_map<int, set<string>>& modifiesRS,
                                    const unordered_map<int, set<string>>& usesRS,
                                    bool findAffectsStar);

unordered_map<int, set<int>> extractAffectsWithMultipleWildcards(const vector<Line>& program,
                                                                 const unordered_map<int, set<int>>& cfg,
                                                                 const set<string>& variables,
                                                                 const unordered_map<int, set<string>>& modifiesRS,
                                                                 const unordered_map<int, set<string>>& usesRS,
                                                                 bool findAffectsStar);

void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths,
         unordered_map<int, int>* visited);
