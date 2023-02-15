#include "AssignTable.h"

AssignTable::AssignTable() = default;

void AssignTable::addAssignNumber(int assignNumber) {
	assignTable.insert(assignNumber);
}

void AssignTable::addAllAssignNumbers(std::set<int> assignNumbers) {
	assignTable = assignNumbers;
}

std::set<int> AssignTable::getAllAssignNumbers() {
	return assignTable;
}