#include "QPS/include/model/SelectClause.h"

SelectClause::SelectClause() {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::string synName) {
    this->synNames.push_back(synName);
}

SelectClause::SelectClause(std::vector<std::string> synNames) {
    this->synNames = synNames;
}

std::vector<std::string> SelectClause::getSynNameVec() {
    return this->synNames;
}
