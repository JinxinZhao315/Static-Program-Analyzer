#pragma once

#include <utility>
#include "CommonExtractorHeader.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
    }
};

void clearCache();

static unordered_map<pair<int, int>, bool, pair_hash> cache;

bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                              const unordered_map<int, set<int>>& cfg,
                                              const unordered_map<int, set<string>>& modifiesRS,
                                              const unordered_map<int, set<string>>& usesRS,
                                              bool findAffectsStar
                                              );

set<int> extractAffectsWithWildcard(const vector<Line>& program, int lineNum, bool wildCardIsFirstArg,
                                    const unordered_map<int, set<int>>& cfg,
                                    const unordered_map<int, set<string>>& modifiesRS,
                                    const unordered_map<int, set<string>>& usesRS,
                                    bool findAffectsStar);

unordered_map<int, set<int>> extractAffectsWithMultipleWildcards(const vector<Line>& program,
                                                                 const unordered_map<int, set<int>>& cfg,
                                                                 const unordered_map<int, set<string>>& modifiesRS,
                                                                 const unordered_map<int, set<string>>& usesRS,
                                                                 bool findAffectsStar);

void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths,
         unordered_map<int, int>* visited);
