#include "pkb/include/table/StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addStatementNumber(std::string statementType, int statementNumber) {
	statementTable.insert(statementNumber);
	auto pair = statementByTypeTable.find(statementType);
	if (pair == statementByTypeTable.end()) {
		statementByTypeTable[statementType] = { statementNumber };
	}
	else {
		statementByTypeTable[statementType].insert(statementNumber);
	}
}

void StatementTable::addAllStatementsByType(std::unordered_map<std::string, std::set<int>> statementsByType) {
	statementByTypeTable = statementsByType;
}

void StatementTable::addAllStatementsRegardlessOfType(std::unordered_map<std::string, std::set<int>> statementsByType) {
	for (const auto& [stmtType, stmtNums] : statementsByType) {
		statementTable.insert(stmtNums.begin(), stmtNums.end());
	}
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

std::set<int> StatementTable::getAllStatementNumbersByType(std::string statementType) {
	return statementByTypeTable[statementType];
}
