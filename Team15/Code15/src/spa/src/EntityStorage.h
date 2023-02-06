#pragma once

#include <set>

using namespace std;

template <typename E>
class EntityStorage {
public:
	inline EntityStorage() = default;

	inline void addEntity(E entity) {
		entityStorage.emplace(entity);
	}

	inline std::set<E> getAllEntities() {
		return entityStorage;
	}

private:
	std::set<E> entityStorage;
};