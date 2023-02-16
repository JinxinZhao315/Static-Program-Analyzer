#include "StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addStatementNumber(string statementType, int statementNumber) {
	statementTable.insert(statementNumber);
	auto pair = statementByTypeTable.find(statementType);
	if (pair == statementByTypeTable.end()) {
		statementByTypeTable[statementType] = { statementNumber };
	}
	else {
		statementByTypeTable[statementType].insert(statementNumber);
	}
}

void StatementTable::addAllStatements(std::set<int> statements) {
	statementTable = statements;
}

void StatementTable::addAllStatementsByType(std::unordered_map<string, std::set<int>> statementsByType) {
	statementByTypeTable = statementsByType;
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

std::set<int> StatementTable::getAllStatementNumbersByType(string statementType) {
	return statementByTypeTable[statementType];
}
