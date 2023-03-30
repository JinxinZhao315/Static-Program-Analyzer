#pragma once

#include <set>
#include <map>
#include <string>
#include <unordered_map>

#include "common/include/models/Keywords.h"

class StatementTable {
public:
	inline StatementTable() = default;

	inline void addAllStatementNumbers(std::unordered_map<KeywordsEnum, std::set<int>> statementsByType) {
		for (const auto& [stmtType, stmtNums] : statementsByType) {
			statementTable.insert(stmtNums.begin(), stmtNums.end());
		}
	}

	inline void addAllStatementNumbersByType(std::unordered_map<KeywordsEnum, std::set<int>> statementsByType) {
		statementByTypeTable = statementsByType;
	}

	inline std::set<int> getAllStatementNumbers() {
		return statementTable;
	}

	inline std::set<int> getAllStatementNumbersByType(KeywordsEnum statementType) {
		return statementByTypeTable[statementType];
	}

private:
	std::set<int> statementTable;
	std::unordered_map<KeywordsEnum, std::set<int> > statementByTypeTable;
};