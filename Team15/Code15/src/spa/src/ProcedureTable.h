#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class ProcedureTable {
public:
	void addProcedureName(std::string ProcedureName);

	std::unordered_set<std::string> getAllProcedureNames();

private:
	std::unordered_set<std::string> procedureTable;
};