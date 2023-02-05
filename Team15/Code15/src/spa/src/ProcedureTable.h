#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class ProcedureTable {
public:
	ProcedureTable();

	void addProcedureName(std::string procedureName);

	std::set<std::string> getAllProcedureNames();

private:
	std::set<std::string> procedureTable;
	size_t tableSize = 0;
};