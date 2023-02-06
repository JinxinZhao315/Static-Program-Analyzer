#include "EntityTable.h"

EntityTable::EntityTable() = default;

void EntityTable::addEntity(std::string entity) {
	entityTable.emplace(entity);
	tableSize++;
}

std::set<std::string> EntityTable::getAllEntities() {
	return entityTable;
}
