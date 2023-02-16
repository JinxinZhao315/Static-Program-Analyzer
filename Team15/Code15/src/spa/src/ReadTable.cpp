#include "ReadTable.h"

ReadTable::ReadTable() = default;

void ReadTable::addReadNumber(int readNumber) {
	readTable.insert(readNumber);
}

std::set<int> ReadTable::getAllReadNumbers() {
	return readTable;
}