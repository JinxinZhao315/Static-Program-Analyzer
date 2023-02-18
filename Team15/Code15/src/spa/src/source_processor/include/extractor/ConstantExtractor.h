#include <string>
#include <set>
#include "common/include/models/Line.h"

using namespace std;

class ConstantExtractor {
private:
    set<string> constants;
public:
    set<string> getConstants();
    void extractConstants(Line line);
};