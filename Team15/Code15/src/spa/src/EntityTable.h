#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class EntityTable {
public:
	EntityTable();

	void addEntity(std::string entity);

	std::set<std::string> getAllEntities();

private:
	std::set<std::string> entityTable;
};