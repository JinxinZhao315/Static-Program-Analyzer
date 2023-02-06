#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class ConstantTable {
public:
	ConstantTable();

	void addConstantValue(std::string constantValue);

	std::set<std::string > getAllConstantValues();

private:
	std::set<std::string > constantTable;
};