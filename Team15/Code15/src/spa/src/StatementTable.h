#pragma once

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStmt(Statement* stmt);

	unordered_set<StatementNumber> getStmtNums();

	Statement* getStmt(const StatementNumber& stmtNum);

	StatementType getStmtType(const StatementNumber& stmtNum);

	unordered_set<StatementNumber> getStmtNumsByType(const StatementType& stmtType);

private:
	unordered_set<Statement*> stmts;
	unordered_set<StatementNumber> stmtNums;
	unordered_map<StatementType, unordered_set<StatementNumber>> stmtNumsByType = {
		{StatementType::READ, {}},
		{StatementType::PRINT, {}},
		{StatementType::ASSIGN, {}},
		{StatementType::CALL, {}},
		{StatementType::WHILE, {}},
		{StatementType::IF, {}},
	};
};