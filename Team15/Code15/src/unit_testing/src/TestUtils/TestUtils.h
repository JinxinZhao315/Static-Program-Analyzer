#pragma once

#include "catch.hpp"
#include "source_processor/include/extractor/CommonExtractorHeader.h"

void printNodes(const unordered_map<int, set<int>>& myMap);

void compareCFG(const unordered_map<int, set<int>>& result, const unordered_map<int, set<int>>& expected);