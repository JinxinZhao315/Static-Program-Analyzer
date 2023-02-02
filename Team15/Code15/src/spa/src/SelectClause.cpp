#include "SelectClause.h"

SelectClause::SelectClause() {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::string varName) {
    this->varName = varName;
}

std::string SelectClause::getVarName() {
    return this->varName;
}
