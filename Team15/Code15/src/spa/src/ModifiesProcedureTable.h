#pragma once

#include <unordered_map>
#include <set>
#include <string>

using namespace std;

class ModifiesProcedureTable {
public:
	ModifiesProcedureTable();

	void addModifiesProcedure(std::string procedure, std::set<std::string> variables);

	std::set<std::string> getVariables(std::string procedure);

	std::set<std::string> getProcedures(std::string variable);

	bool inRelationship(std::string procedureName, std::string variableName);

	bool isEmpty();

	void addVariables(std::string procedure, std::set<std::string> variables);

	void addProcedures(std::string procedure, std::set<std::string> variables);

private:
	std::unordered_map<std::string, std::set<std::string>> procedureToVariablesMap;
	std::unordered_map<std::string, std::set<std::string>> variableToProceduresMap;
};