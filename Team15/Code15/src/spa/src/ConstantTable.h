#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class ConstantTable {
public:
	ConstantTable();

	void addConstantValue(std::string ConstantValue);

	std::unordered_set<int> getAllConstantValues();

	size_t getTableSize();

private:
	std::unordered_set<int> constantTable;
	size_t tableSize = 0;
};