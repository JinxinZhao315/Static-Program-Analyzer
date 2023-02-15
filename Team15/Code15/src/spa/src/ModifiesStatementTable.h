#pragma once

#include <unordered_map>
#include <set>
#include <string>

using namespace std;

class ModifiesStatementTable {
public:
	ModifiesStatementTable();

	void addModifiesStatement(int statement, std::set<std::string> variables);

	void addAllModifiesStatement(std::unordered_map<int, std::set<std::string>> statementToVariables);

	std::set<std::string> getVariables(int statement);

	std::set<int> getStatements(std::string variable);

	bool inRelationship(int statementNumber, std::string variableName);

	bool isEmpty();

	void addVariables(int statement, std::set<std::string> variables);

	void addStatements(int statement, std::set<std::string> variables);

	void flipStatementToVariables(std::unordered_map<int, std::set<std::string>> statementToVariables);

private:
	std::unordered_map<int, std::set<std::string>> statementToVariablesMap;
	std::unordered_map<std::string, std::set<int>> variableToStatementsMap;
};