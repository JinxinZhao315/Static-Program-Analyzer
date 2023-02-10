#pragma once

#include "Extractor.h"

tuple<map<int, int>, map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program, const map<int, int>& parentsRS);