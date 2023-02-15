#include "EntityStorage.h"

EntityStorage::EntityStorage() = default;

void EntityStorage::addEntity(std::string entity) {
	entityStorage.insert(entity);
}

std::set<std::string> EntityStorage::getAllEntities() {
	return entityStorage;
}