#pragma once

#include <string>
#include <set>

using namespace std;

template <typename E>
class EntityTable {
public:
	inline EntityTable() = default;

	inline void addEntity(E entity) {
		entityTable.insert(entity);
	}

	inline std::set<E> getAllEntities() {
		return entityTable;
	}

private:
	std::set<std::string> entityTable;
};