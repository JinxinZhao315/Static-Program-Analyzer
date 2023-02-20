#include "pkb/include/table/ProcedureTable.h"

ProcedureTable::ProcedureTable() = default;

void ProcedureTable::addProcedureName(std::string procedureName) {
	procedureTable.insert(procedureName);
}

void ProcedureTable::addAllProcedureNames(std::set<std::string> procedureNames) {
	procedureTable = procedureNames;
}

std::set<std::string> ProcedureTable::getAllProcedureNames() {
	return procedureTable;
}
