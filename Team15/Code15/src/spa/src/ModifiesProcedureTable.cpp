#include "ModifiesProcedureTable.h"

ModifiesProcedureTable::ModifiesProcedureTable() = default;

void ModifiesProcedureTable::addModifiesProcedure(std::string procedure, std::set<std::string> variables) {
	addVariables(procedure, variables);
	addProcedures(procedure, variables);
}

void ModifiesProcedureTable::addAllModifiesProcedure(std::unordered_map<std::string, std::set<std::string>> procedureToVariables) {
	procedureToVariablesMap = procedureToVariables;
	flipProcedureToVariables(procedureToVariables);
}

std::set<std::string> ModifiesProcedureTable::getVariables(std::string procedure) {
	auto pair = procedureToVariablesMap.find(procedure);
	if (pair == procedureToVariablesMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::string> ModifiesProcedureTable::getProcedures(std::string variable) {
	auto pair = variableToProceduresMap.find(variable);
	if (pair == variableToProceduresMap.end()) {
		return {};
	}
	return pair->second;
}

bool ModifiesProcedureTable::inRelationship(std::string procedureName, std::string variableName) {
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

bool ModifiesProcedureTable::isEmpty() {
	return procedureToVariablesMap.empty() && variableToProceduresMap.empty();
}

void ModifiesProcedureTable::addVariables(std::string procedure, std::set<std::string> variables) {
	auto pair = procedureToVariablesMap.find(procedure);
	if (pair == procedureToVariablesMap.end()) {
		procedureToVariablesMap[procedure] = variables;
	}
	else {
		pair->second.insert(variables.begin(), variables.end());
	}
}

void ModifiesProcedureTable::addProcedures(std::string procedure, std::set<std::string> variables) {
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

void ModifiesProcedureTable::flipProcedureToVariables(std::unordered_map<std::string, std::set<std::string>> procedureToVariables) {
	for (const auto& [key, values] : procedureToVariables) {
		for (std::string value : values) {
			auto pair = variableToProceduresMap.find(value);
			if (pair == variableToProceduresMap.end()) {
				variableToProceduresMap[value] = { key };
			}
			else {
				pair->second.insert(key);
			}
		}
	}
}