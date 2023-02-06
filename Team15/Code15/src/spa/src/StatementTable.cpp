#include "StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addStatementNumber(int statementNumber) {
	statementTable.emplace(statementNumber);
	tableSize++;
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

size_t StatementTable::getTableSize() {
	return tableSize;
}