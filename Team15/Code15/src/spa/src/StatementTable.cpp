#include "StatementTable.h"

StatementTable::StatementTable() = default;

void StatementTable::addStatementNumber(Tokens::Keyword statementType, int statementNumber) {
	statementTable.emplace(statementNumber);
	statementByTypeTable[statementType].emplace(statementNumber);
}

std::set<int> StatementTable::getAllStatementNumbers() {
	return statementTable;
}

std::set<int> StatementTable::getAllStatementNumbersByType(Tokens::Keyword statementType) {
	return statementByTypeTable[statementType];
}
