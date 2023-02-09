
#include "SynonymTable.h"

SynonymTable::SynonymTable() {}

void SynonymTable::addSynonTypePair(std::string synonName, std::string type) {
    this->synonTable.insert({synonName, type});
}

std::string SynonymTable::getTypeFromSynon(std::string type) {
    return this->synonTable.find(type)->second;
}