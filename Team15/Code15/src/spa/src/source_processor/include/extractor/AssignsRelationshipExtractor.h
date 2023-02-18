#pragma once

#include "CommonExtractorHeader.h"

unordered_map<string, set<Line> > extractAssignmentRS(const vector<Line>& program, const set<string>& variables);