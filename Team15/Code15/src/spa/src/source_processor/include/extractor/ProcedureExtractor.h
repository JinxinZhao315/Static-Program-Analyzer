#pragma once

#include "CommonExtractorHeader.h"

class ProcedureExtractor {
private:
    set<string> procedures;
public:
    set<string> getProcedures();
    void extractProcedures(Line line);
};