#pragma once

#include "CommonExtractorHeader.h"

set<Line> extractConditionalRS(const string& conditionType, const vector<Line>& program, const set<string>& variables);