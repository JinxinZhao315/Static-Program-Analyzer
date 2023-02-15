#include "IfTable.h"

IfTable::IfTable() = default;

void IfTable::addIfNumber(int ifNumber) {
	ifTable.insert(ifNumber);
}

std::set<int> IfTable::getAllIfNumbers() {
	return ifTable;
}