#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class ConstantTable {
public:
	void addConstantValue(std::string ConstantValue);

	std::unordered_set<int> getAllConstantValues();

private:
	std::unordered_set<int> constantTable;
};