#pragma once

#include <set>
#include <string>
#include <vector>

#include "common/include/models/Line.h"

template <typename E>
class EntityTable {
public:
	inline EntityTable() = default;

	inline void addAllEntities(std::set<E> entities) {
		entitySet = entities;
	}

	inline void addAllEntities(std::vector<E> entities) {
		entityVector = entities;
	}

	inline std::set<E> getEntitySet() {
		return entitySet;
	}

	inline std::vector<E> getEntityVector() {
		return entityVector;
	}

private:
	std::set<E> entitySet;
	std::vector<E> entityVector;
};