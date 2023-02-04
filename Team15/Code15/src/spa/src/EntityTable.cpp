#include "EntityTable.h"

EntityTable::EntityTable() = default;

void EntityTable::addEntity(std::string constantValue) {
	entityTable.emplace(constantValue);
	tableSize++;
}

std::set<std::string> EntityTable::getAllEntities() {
	return entityTable;
}

size_t EntityTable::getTableSize() {
	return tableSize;
}