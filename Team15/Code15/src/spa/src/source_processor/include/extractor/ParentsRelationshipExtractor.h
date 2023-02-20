#pragma once

#include "CommonExtractorHeader.h"

tuple<unordered_map<int, set<int>>, unordered_map<int, set<int> >> extractParentsRelationship(const vector<Line>& program);