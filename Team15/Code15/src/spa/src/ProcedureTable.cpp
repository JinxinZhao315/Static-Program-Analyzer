#include "ProcedureTable.h"

ProcedureTable::ProcedureTable() = default;

void ProcedureTable::addProcedureName(std::string procedureName) {
	procedureTable.insert(procedureName);
}

std::set<std::string> ProcedureTable::getAllProcedureNames() {
	return procedureTable;
}
