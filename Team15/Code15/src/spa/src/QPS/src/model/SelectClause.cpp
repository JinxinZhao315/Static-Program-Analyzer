#include "QPS/include/model/SelectClause.h"

SelectClause::SelectClause() {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::vector<Elem> synNames) {
    this->synNames = synNames;
}

std::vector<Elem> SelectClause::getSynNameVec() {
    return this->synNames;
}
