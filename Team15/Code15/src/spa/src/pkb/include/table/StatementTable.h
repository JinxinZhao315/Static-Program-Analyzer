#pragma once

#include <set>
#include <map>
#include <string>

#include <unordered_map>

class StatementTable {
public:
	inline StatementTable() = default;

	inline void addAllStatementNumbers(std::unordered_map<std::string, std::set<int>> statementsByType) {
		for (const auto& [stmtType, stmtNums] : statementsByType) {
			statementTable.insert(stmtNums.begin(), stmtNums.end());
		}
	}

	inline void addAllStatementNumbersByType(std::unordered_map<std::string, std::set<int>> statementsByType) {
		statementByTypeTable = statementsByType;
	}

	inline std::set<int> getAllStatementNumbers() {
		return statementTable;
	}

	inline std::set<int> getAllStatementNumbersByType(std::string statementType) {
		return statementByTypeTable[statementType];
	}

private:
	std::set<int> statementTable;
	std::unordered_map<std::string, std::set<int> > statementByTypeTable;
};