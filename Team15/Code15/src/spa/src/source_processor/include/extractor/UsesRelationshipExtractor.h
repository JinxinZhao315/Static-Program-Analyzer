#pragma once

#include "Extractor.h"

unordered_map<int, set<string>> extractUsesRS(const vector<Line>& program, const set<string>& variables);