#pragma once

#include <utility>
#include "CommonExtractorHeader.h"

struct tuple_hash {
    template <class T1, class T2, class T3>
    std::size_t operator() (const std::tuple<T1, T2, T3>& t) const {
        return std::hash<T1>{}(std::get<0>(t)) ^ std::hash<T2>{}(std::get<1>(t)) ^ std::hash<T3>{}(std::get<2>(t));
    }
};

void clearCache();

static unordered_map<tuple<int, int, bool>, bool, tuple_hash> cache;


bool extractAffectsRS(const vector<Line>& program, int lineNum1, int lineNum2,
                                              const unordered_map<int, set<int>>& cfg,
                                              const unordered_map<int, set<string>>& modifiesRS,
                                              const unordered_map<int, set<string>>& usesRS,
                                              bool findAffectsStar, const unordered_map<int, Line>& lineNumToLineMap
                                              );

set<int> extractAffectsWithWildcard(const vector<Line>& program, int lineNum, bool wildCardIsFirstArg,
                                    const unordered_map<int, set<int>>& cfg,
                                    const unordered_map<int, set<string>>& modifiesRS,
                                    const unordered_map<int, set<string>>& usesRS,
                                    bool findAffectsStar, const unordered_map<int, Line>& lineNumToLineMap
                                    );

unordered_map<int, set<int>> extractAffectsWithMultipleWildcards(const vector<Line>& program,
                                                                 const unordered_map<int, set<int>>& cfg,
                                                                 const unordered_map<int, set<string>>& modifiesRS,
                                                                 const unordered_map<int, set<string>>& usesRS,
                                                                 bool findAffectsStar, unordered_map<int, Line> lineNumToLineMap
                                                                 );

void dfs(unordered_map<int, set<int>> cfg, int lineNum1, int lineNum2, vector<int>* path, vector<vector<int>>* paths,
         unordered_map<int, int>* visited);
