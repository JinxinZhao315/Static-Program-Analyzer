#include "IfTable.h"

IfTable::IfTable() = default;

void IfTable::addIfNumber(int ifNumber) {
	ifTable.insert(ifNumber);
}

void IfTable::addAllIfNumbers(std::set<int> ifNumbers) {
	ifTable = ifNumbers;
}

std::set<int> IfTable::getAllIfNumbers() {
	return ifTable;
}