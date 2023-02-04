#include "VariableTable.h"

VariableTable::VariableTable() = default;

void VariableTable::addVariableName(std::string variableName) {
	variableTable.emplace(variableName);
	tableSize++;
}

std::unordered_set<std::string> VariableTable::getAllVariableNames() {
	return variableTable;
}

size_t VariableTable::getTableSize() {
	return tableSize;
}