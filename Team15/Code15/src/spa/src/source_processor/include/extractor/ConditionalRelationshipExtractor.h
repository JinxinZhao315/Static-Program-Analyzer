#pragma once

#include "CommonExtractorHeader.h"

unordered_map<string, set<Line>> extractConditionalRS(const string& conditionType, const vector<Line>& program, const set<string>& variables);