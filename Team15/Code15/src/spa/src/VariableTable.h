#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class VariableTable {
public:
	void addVariableName(std::string VariableName);

	std::unordered_set<std::string> getAllVariableNames();

private:
	std::unordered_set<std::string> variableTable;
};