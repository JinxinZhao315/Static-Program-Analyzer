#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStatementNumber(int statementNumber);

	std::set<int> getAllStatementNumbers();

	size_t getTableSize();

private:
	std::set<int> statementTable;
	size_t tableSize = 0;
};