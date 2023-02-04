#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class VariableTable {
public:
	VariableTable();

	void addVariableName(std::string variableName);

	std::set<std::string> getAllVariableNames();

	size_t getTableSize();

private:
	std::set<std::string> variableTable;
	size_t tableSize = 0;
};