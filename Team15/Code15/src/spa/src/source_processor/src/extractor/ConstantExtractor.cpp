#include "source_processor/include/extractor/ConstantExtractor.h"
#include "common/include/models/Line.h"

bool isNumeric(const string& token) {
    try {
        stoi(token);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

void ConstantExtractor::extractConstants(Line line) {
    vector<string> tokens = line.getTokens();
    set<string> *c = &this->constants;
    for (auto token = begin(tokens); token != end(tokens); token++) {
        if (isNumeric(*token)) {
            c->insert(*token);
        }
    }
}

set<string> ConstantExtractor::getConstants() {
    return constants;
}
