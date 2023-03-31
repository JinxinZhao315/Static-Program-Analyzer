#include "QPS/include/model/SelectClause.h"

SelectClause::SelectClause() : Clause(SELECT) {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::vector<Elem> synNames) : Clause(SELECT) {
    this->synNames = synNames;
}

std::vector<Elem> SelectClause::getSynNameVec() {
    return this->synNames;
}
