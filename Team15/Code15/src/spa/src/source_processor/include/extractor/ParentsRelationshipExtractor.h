#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

tuple<unordered_map<int, int>, unordered_map<int, set<int> >> extractParentsRelationship(const vector<Line>& program);