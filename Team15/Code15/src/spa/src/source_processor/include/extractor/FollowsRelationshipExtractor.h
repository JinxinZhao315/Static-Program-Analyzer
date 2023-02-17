#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

tuple<unordered_map<int, int>, unordered_map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program);