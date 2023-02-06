#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <map>

#include "Tokens.h"

using namespace std;

class StatementTable {
public:
	StatementTable();

	void addStatementNumber(int statementNumber);

	void addStatementNumberByType(int statementNumber, Tokens::Keyword statementType);

	std::set<int> getAllStatementNumbers();

	std::set<int> StatementTable::getAllStatementNumbersByType(Tokens::Keyword statementType);

private:
	std::set<int> statementTable;
	std::map<Tokens::Keyword, set<int>> statementByTypeTable = {
		{Tokens::Keyword::READ, {}},
		{Tokens::Keyword::PRINT, {}},
		{Tokens::Keyword::ASSIGN, {}},
		{Tokens::Keyword::CALL, {}},
		{Tokens::Keyword::WHILE, {}},
		{Tokens::Keyword::IF, {}}
	};
};