#include "VariableTable.h"

VariableTable::VariableTable() = default;

void VariableTable::addVariableName(std::string variableName) {
	variableTable.insert(variableName);
}

std::set<std::string> VariableTable::getAllVariableNames() {
	return variableTable;
}
