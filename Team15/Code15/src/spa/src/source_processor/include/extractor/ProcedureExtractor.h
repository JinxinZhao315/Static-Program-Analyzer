#include "source_processor/include/extractor/CommonExtractorHeader.h"

class ProcedureExtractor {
public:
    void extractProcedures(const vector<Line>& program);
    void extractCallLineNumToProcName(const vector<Line>& program);
    set<string> getProcedures();
    unordered_map<int, string> getCallLineNumToProcName();
    string findProcedure(vector<string> tokens);
private:
    set<string> procedures;
    unordered_map<int, string> callLineNumToProcName;
};
