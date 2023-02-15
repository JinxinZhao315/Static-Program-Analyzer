#include "ReadTable.h"

ReadTable::ReadTable() = default;

void ReadTable::addReadNumber(int readNumber) {
	readTable.insert(readNumber);
}

void ReadTable::addAllReadNumbers(std::set<int> readNumbers) {
	readTable = readNumbers;
}

std::set<int> ReadTable::getAllReadNumbers() {
	return readTable;
}