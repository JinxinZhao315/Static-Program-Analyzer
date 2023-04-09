#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/include/models/Line.h"

template <typename E>
class EntityTable {
public:
	inline EntityTable() = default;

	inline void addEntityToSet(E entity) {
		entitySet.insert(entity);
	}

	inline void addAllEntities(std::set<E> entities) {
		entitySet = entities;
	}

	inline void addAllEntities(std::vector<E> entities) {
		entityVector = entities;
	}

	inline void addEntityMapping(int entityId, E entity) {
		entityMap[entityId] = entity;
	}

	inline std::set<E> getEntitySet() {
		return entitySet;
	}

	inline std::vector<E> getEntityVector() {
		return entityVector;
	}

	inline std::unordered_map<int, E> getEntityMap() {
		return entityMap;
	}

private:
	std::set<E> entitySet;
	std::vector<E> entityVector;
	std::unordered_map<int, E> entityMap;
};