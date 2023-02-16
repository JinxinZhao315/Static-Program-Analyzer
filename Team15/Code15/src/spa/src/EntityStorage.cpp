#include "EntityStorage.h"

EntityStorage::EntityStorage() = default;

void EntityStorage::addEntity(std::string entity) {
	entityStorage.insert(entity);
}

void EntityStorage::addAllEntities(std::set<std::string> entities) {
	entityStorage = entities;
}

std::set<std::string> EntityStorage::getAllEntities() {
	return entityStorage;
}