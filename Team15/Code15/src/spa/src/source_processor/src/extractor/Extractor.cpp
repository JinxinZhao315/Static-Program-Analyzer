#include "../../include/extractor/Extractor.h"

void Extractor::extract(const vector<Line> &program) {
    // call and get results of extraction
    void generateParentsRelationship(program);

    // TODO: set results here
    this->parentsRS = parentsRS;
    this->parentsStar = parentsStarRS;
}
