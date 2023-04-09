#include "../../include/model/Clause.h"

Clause::Clause(ClauseType clauseType) {
    this->clauseType = clauseType;
}

void Clause::setSynList(std::vector<std::string> synList) {
    this->synList = synList;
}

std::vector<std::string> Clause::getSynList() {
    return this->synList;
}

void Clause::addSyn(std::string syn) {
    this->synList.push_back(syn);
}

ClauseType Clause::getType() {
    return this->clauseType;
}