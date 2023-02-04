#include "ConstantTable.h"

ConstantTable::ConstantTable() = default;

void ConstantTable::addConstantValue(std::string ConstantValue) {
	constantTable.emplace(ConstantValue);
	tableSize++;
}

std::unordered_set<int> ConstantTable::getAllConstantValues() {
	return constantTable;
}

size_t ConstantTable::getTableSize() {
	return tableSize;
}