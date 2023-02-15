#include "AssignTable.h"

AssignTable::AssignTable() = default;

void AssignTable::addAssignNumber(int assignNumber) {
	assignTable.insert(assignNumber);
}

std::set<int> AssignTable::getAllAssignNumbers() {
	return assignTable;
}