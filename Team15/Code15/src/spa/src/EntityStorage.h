#pragma once

#include <stdio.h>
#include <iostream>
#include <set>

using namespace std;

template <typename E>
class EntityStorage {
public:
	inline EntityStorage() = default;

	inline void addEntity(E entity) {
		entityStorage.emplace(entity);
		tableSize++;
	}

	inline std::set<E> getAllEntities() {
		return entityStorage;
	}

	inline size_t getTableSize() {
		return tableSize;
	}

private:
	std::set<E> entityStorage;
	size_t tableSize = 0;
};