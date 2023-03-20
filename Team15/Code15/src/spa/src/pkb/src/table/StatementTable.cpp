#include "pkb/include/table/StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addAllStatementNumbers(std::unordered_map<std::string, std::set<int>> statementsByType) {
	for (const auto& [stmtType, stmtNums] : statementsByType) {
		statementTable.insert(stmtNums.begin(), stmtNums.end());
	}
}

void StatementTable::addAllStatementNumbersByType(std::unordered_map<std::string, std::set<int>> statementsByType) {
	statementByTypeTable = statementsByType;
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

std::set<int> StatementTable::getAllStatementNumbersByType(std::string statementType) {
	return statementByTypeTable[statementType];
}
