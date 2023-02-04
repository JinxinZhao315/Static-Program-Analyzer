#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class ProcedureTable {
public:
	ProcedureTable();

	void addProcedureName(std::string ProcedureName);

	std::unordered_set<std::string> getAllProcedureNames();

	size_t getTableSize();

private:
	std::unordered_set<std::string> procedureTable;
	size_t tableSize = 0;
};