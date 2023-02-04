#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class VariableTable {
public:
	VariableTable();

	void addVariableName(std::string VariableName);

	std::unordered_set<std::string> getAllVariableNames();

	size_t getTableSize();

private:
	std::unordered_set<std::string> variableTable;
	size_t tableSize = 0;
};