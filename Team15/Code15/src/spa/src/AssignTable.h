#pragma once

#include <set>

using namespace std;

class AssignTable {
public:
	AssignTable();

	void addAssignNumber(int assignNumber);

	std::set<int> getAllAssignNumbers();

private:
	std::set<int> assignTable;
};