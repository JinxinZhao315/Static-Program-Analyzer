#pragma once

#include <string>
#include <set>

using namespace std;

class ProcedureTable {
public:
	ProcedureTable();

	void addProcedureName(std::string procedureName);

	void addAllProcedureNames(std::set<std::string> procedureNames);

	std::set<std::string> getAllProcedureNames();

private:
	std::set<std::string> procedureTable;
};