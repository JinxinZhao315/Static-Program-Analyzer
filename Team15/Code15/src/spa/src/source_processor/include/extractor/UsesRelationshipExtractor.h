#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

unordered_map<int, set<string>> extractUsesRS(const vector<Line>& program, const set<string>& variables);