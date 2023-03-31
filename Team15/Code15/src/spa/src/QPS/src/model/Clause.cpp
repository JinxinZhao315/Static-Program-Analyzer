#include "../../include/model/Clause.h"

Clause::Clause(Utility::clauseType clauseType) {
    this->clauseType = clauseType;
}

void Clause::setSynList(std::set<std::string> synList) {
    this->synList = synList;
}

std::set<std::string> Clause::getSynList() {
    return this->synList;
}

void Clause::addSyn(std::string syn) {
    this->synList.add(syn);
}

ClauseType Clause::getType() {
    return this->clauseType;
}