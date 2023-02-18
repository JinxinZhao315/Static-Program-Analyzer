#include <string>
#include <set>
#include "common/include/models/Line.h"

using namespace std;

class ProcedureExtractor {
private:
    set<string> procedures;
public:
    set<string> getProcedures();
    void extractProcedures(Line line);
};