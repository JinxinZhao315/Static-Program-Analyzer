#include "source_processor/include/extractor/CommonExtractorHeader.h"
#include "common/include/models/Keywords.h"

class VariableExtractor {
private:
    Keywords* keywords;
public:
    VariableExtractor();
    set<string> extractVariables(const vector<Line>& program);
    bool isVariable(string token, string previous);
};
