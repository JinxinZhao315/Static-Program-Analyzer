#pragma once

#include "CommonExtractorHeader.h"

unordered_map<int, set<int>> extractNextRS(const vector<Line>& program, const unordered_map<int, int>& followsRS);

unordered_map<int, set<int>> extractNextStarRS(const unordered_map<int, set<int>>& nextRS);