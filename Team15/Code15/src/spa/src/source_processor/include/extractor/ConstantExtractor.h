#pragma once

#include "CommonExtractorHeader.h"

class ConstantExtractor {
private:
    set<string> constants;
public:
    set<string> getConstants();
    void extractConstants(Line line);
};