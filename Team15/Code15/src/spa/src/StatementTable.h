#pragma once

#include <set>
#include <map>
#include <string>

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStatementNumber(int statementNumber);

	void addStatementNumberByType(int statementNumber, string statementType);

	std::set<int> getAllStatementNumbers();

	std::set<int> getAllStatementNumbersByType(string statementType);

private:
	std::set<int> statementTable;
	std::map<string, std::set<int>> statementByTypeTable = {
		{"read", {}},
		{"print", {}},
		{"=", {}},
		{"call", {}},
		{"while", {}},
		{"if", {}}
	};
};