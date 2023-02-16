#pragma once

#include <set>
#include <map>
#include <string>

#include <unordered_map>

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStatementNumber(string statementType, int statementNumber);

	void addStatementNumberByType(int statementNumber, string statementType);

	void addAllStatements(std::set<int> statements);

	void addAllStatementsByType(std::unordered_map<string, std::set<int>> statementsByType);

	std::set<int> getAllStatementNumbers();

	std::set<int> getAllStatementNumbersByType(string statementType);

private:
	std::set<int> statementTable;
	std::unordered_map<string, std::set<int>> statementByTypeTable = {
		{"read", {}},
		{"print", {}},
		{"=", {}},
		{"call", {}},
		{"while", {}},
		{"if", {}}
	};
};