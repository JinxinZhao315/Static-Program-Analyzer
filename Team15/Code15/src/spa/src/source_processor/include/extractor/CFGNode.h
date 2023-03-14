#pragma once

#include "CommonExtractorHeader.h"

struct CFGNode {
    int startLine;
    int endLine;
    set<int> next;

    CFGNode(int startLine, int endLine) : startLine(startLine), endLine(endLine) {}
};
