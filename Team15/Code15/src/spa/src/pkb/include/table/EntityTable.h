#pragma once

#include <string>
#include <set>

template <typename E>
class EntityTable {
public:
	inline EntityTable() = default;

	inline void addEntity(E entity) {
		entityTable.insert(entity);
	}

	inline void addAllEntities(std::set<E> entities) {
		entityTable = entities;
	}

	inline std::set<E> getAllEntities() {
		return entityTable;
	}

private:
	std::set<E> entityTable;
};