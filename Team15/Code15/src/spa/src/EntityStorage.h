#pragma once

#include <string>
#include <set>

using namespace std;

class EntityStorage {
public:
	EntityStorage();

	void addEntity(std::string entity);

	std::set<std::string> getAllEntities();

private:
	std::set<std::string> entityStorage;
};