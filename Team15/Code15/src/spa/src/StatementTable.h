#pragma once

#include <set>
#include <string>
#include <unordered_map>

#include "Tokens.h"

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStatementNumber(Tokens::Keyword statementType, int statementNumber);

	void addAllStatements(std::set<int> statements);

	void addAllStatementsByType(std::unordered_map<Tokens::Keyword, std::set<int>> statementsByType);

	std::set<int> getAllStatementNumbers();

	std::set<int> getAllStatementNumbersByType(Tokens::Keyword statementType);

private:
	std::set<int> statementTable;
	std::unordered_map<Tokens::Keyword, std::set<int>> statementByTypeTable;
};