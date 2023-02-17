#include "pkb/include/table/VariableTable.h"

VariableTable::VariableTable() = default;

void VariableTable::addVariableName(std::string variableName) {
	variableTable.insert(variableName);
}

void VariableTable::addAllVariableNames(std::set<std::string> variableNames) {
	variableTable = variableNames;
}

std::set<std::string> VariableTable::getAllVariableNames() {
	return variableTable;
}
