#include "../../include/extractor/Extractor.h"

void Extractor::extract(const vector<Line> &program) {
    // Call and get results of extraction
    auto [parentsRS, parentsStarRS] = extractParentsRelationship(program);
    auto [followsRS, followsStarRS] = extractFollowsRelationship(program, parentsRS);
    // Set results here
    this->parentsRS = parentsRS;
    this->parentsStarRS = parentsStarRS;
    this->nestingLevel = nestingLevel;
}
