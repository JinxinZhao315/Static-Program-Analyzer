#include "ProcedureTable.h"

ProcedureTable::ProcedureTable() = default;

void ProcedureTable::addProcedureName(std::string procedureName) {
	procedureTable.emplace(procedureName);
	tableSize++;
}

std::set<std::string> ProcedureTable::getAllProcedureNames() {
	return procedureTable;
}
