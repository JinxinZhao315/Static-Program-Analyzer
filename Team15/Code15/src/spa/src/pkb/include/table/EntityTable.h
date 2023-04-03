#pragma once

#include <string>
#include <set>

#include "common/include/models/Line.h"

template <typename E>
class EntityTable {
public:
	inline EntityTable() = default;

	inline void addAllEntities(std::set<E> entities) {
		entityTable = entities;
	}

	inline std::set<E> getAllEntities() {
		return entityTable;
	}

private:
	std::set<E> entityTable;
};