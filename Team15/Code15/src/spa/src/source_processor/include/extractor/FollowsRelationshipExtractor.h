#pragma once

#include "Extractor.h"

pair<map<int, int>, map<int, set<int> > > extractFollowsRelationship(const vector<Line>& program);