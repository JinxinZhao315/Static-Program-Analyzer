#pragma once

#include <set>
#include <map>
#include <string>

#include <unordered_map>

class StatementTable {
public:
	StatementTable();

	void addAllStatementNumbers(std::unordered_map<std::string, std::set<int>> statementsByType);

	void addAllStatementNumbersByType(std::unordered_map<std::string, std::set<int>> statementsByType);

	std::set<int> getAllStatementNumbers();

	std::set<int> getAllStatementNumbersByType(std::string statementType);

private:
	std::set<int> statementTable;
	std::unordered_map<std::string, std::set<int> > statementByTypeTable;
};