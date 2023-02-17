#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

unordered_map<int, set<string>> extractModifiesRS(const vector<Line>& program);
