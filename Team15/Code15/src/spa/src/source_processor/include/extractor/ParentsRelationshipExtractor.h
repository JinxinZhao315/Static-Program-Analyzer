#pragma once

#include "Extractor.h"

tuple<map<int, int>, map<int, set<int> >> extractParentsRelationship(const vector<Line>& program);