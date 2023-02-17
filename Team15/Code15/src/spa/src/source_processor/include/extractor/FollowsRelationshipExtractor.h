#pragma once

#include "CommonExtractorHeader.h"

using namespace std;

tuple<map<int, int>, map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program);