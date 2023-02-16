#include "StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addStatementNumber(int statementNumber) {
	statementTable.emplace(statementNumber);
}

void StatementTable::addStatementNumberByType(int statementNumber, string statementType) {
	statementByTypeTable[statementType].emplace(statementNumber);
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

std::set<int> StatementTable::getAllStatementNumbersByType(string statementType) {
	return statementByTypeTable[statementType];
}
