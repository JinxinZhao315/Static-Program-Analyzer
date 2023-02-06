#include "VariableTable.h"

VariableTable::VariableTable() = default;

void VariableTable::addVariableName(std::string variableName) {
	variableTable.emplace(variableName);
}

std::set<std::string> VariableTable::getAllVariableNames() {
	return variableTable;
}
