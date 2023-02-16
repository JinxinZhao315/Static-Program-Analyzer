#include "ConstantTable.h"

ConstantTable::ConstantTable() = default;

void ConstantTable::addConstantValue(std::string constantValue) {
	constantTable.insert(constantValue);
}

void ConstantTable::addAllConstantValues(std::set<std::string> constantValues) {
	constantTable = constantValues;
}

std::set<std::string> ConstantTable::getAllConstantValues() {
	return constantTable;
}
