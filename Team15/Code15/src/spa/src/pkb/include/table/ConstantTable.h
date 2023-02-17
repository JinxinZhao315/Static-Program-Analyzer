#pragma once

#include <string>
#include <set>

using namespace std;

class ConstantTable {
public:
	ConstantTable();

	void addConstantValue(std::string constantValue);

	void addAllConstantValues(std::set<std::string> constantValues);

	std::set<std::string> getAllConstantValues();

private:
	std::set<std::string> constantTable;
};