#include "UsesProcedureTable.h"

UsesProcedureTable::UsesProcedureTable() = default;

void UsesProcedureTable::addUsesProcedure(std::string procedure, std::set<std::string> variables) {
	addVariables(procedure, variables);
	addProcedures(procedure, variables);
}

std::set<std::string> UsesProcedureTable::getVariables(std::string procedure) {
	auto pair = procedureToVariablesMap.find(procedure);
	if (pair == procedureToVariablesMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::string> UsesProcedureTable::getProcedures(std::string variable) {
	auto pair = variableToProceduresMap.find(variable);
	if (pair == variableToProceduresMap.end()) {
		return {};
	}
	return pair->second;
}

bool UsesProcedureTable::inRelationship(std::string procedureName, std::string variableName) {
	auto pair = procedureToVariablesMap.find(procedureName);
	if (pair == procedureToVariablesMap.end()) {
		return false;
	}
	auto variables = pair->second;
	auto variable = variables.find(variableName);
	if (variable == variables.end()) {
		return false;
	}
	return true;
}

bool UsesProcedureTable::isEmpty() {
	return procedureToVariablesMap.empty() && variableToProceduresMap.empty();
}

void UsesProcedureTable::addVariables(std::string procedure, std::set<std::string> variables) {
	auto pair = procedureToVariablesMap.find(procedure);
	if (pair == procedureToVariablesMap.end()) {
		procedureToVariablesMap[procedure] = variables;
	}
	else {
		pair->second.insert(variables.begin(), variables.end());
	}
}

void UsesProcedureTable::addProcedures(std::string procedure, std::set<std::string> variables) {
	std::set<std::string>::iterator variable;
	for (variable = variables.begin(); variable != variables.end(); variable++) {
		auto pair = variableToProceduresMap.find(*variable);
		if (pair == variableToProceduresMap.end()) {
			variableToProceduresMap[*variable] = { procedure };
		}
		else {
			pair->second.insert(procedure);
		}
	}
}