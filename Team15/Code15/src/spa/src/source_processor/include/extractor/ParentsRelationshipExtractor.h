#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

tuple<map<int, int>, map<int, set<int> >> extractParentsRelationship(const vector<Line>& program);