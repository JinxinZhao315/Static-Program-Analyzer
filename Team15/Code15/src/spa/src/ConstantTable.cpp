#include "ConstantTable.h"

ConstantTable::ConstantTable() = default;

void ConstantTable::addConstantValue(std::string constantValue) {
	constantTable.emplace(constantValue);
	tableSize++;
}

std::set<std::string> ConstantTable::getAllConstantValues() {
	return constantTable;
}
