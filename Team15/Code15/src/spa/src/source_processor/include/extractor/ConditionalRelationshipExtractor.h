#pragma once

#include "CommonExtractorHeader.h"

set<Line> extractConditionalRS(string conditionType, const vector<Line>& program, const set<string>& variables);