#include "pkb/include/table/UsesStatementTable.h"

UsesStatementTable::UsesStatementTable() = default;

void UsesStatementTable::addUsesStatement(int statement, std::set<std::string> variables) {
	addVariables(statement, variables);
	addStatements(statement, variables);
}

void UsesStatementTable::addAllUsesStatement(std::unordered_map<int, std::set<std::string>> statementToVariables) {
	statementToVariablesMap = statementToVariables;
	flipStatementToVariables(statementToVariables);
}

std::set<std::string> UsesStatementTable::getVariables(int statement) {
	auto pair = statementToVariablesMap.find(statement);
	if (pair == statementToVariablesMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> UsesStatementTable::getStatements(std::string variable) {
	auto pair = variableToStatementsMap.find(variable);
	if (pair == variableToStatementsMap.end()) {
		return {};
	}
	return pair->second;
}

bool UsesStatementTable::inRelationship(int statementNumber, std::string variableName) {
	auto pair = statementToVariablesMap.find(statementNumber);
	if (pair == statementToVariablesMap.end()) {
		return false;
	}
	auto variables = pair->second;
	auto variable = variables.find(variableName);
	if (variable == variables.end()) {
		return false;
	}
	return true;
}

bool UsesStatementTable::isEmpty() {
	return statementToVariablesMap.empty() && variableToStatementsMap.empty();
}

void UsesStatementTable::addVariables(int statement, std::set<std::string> variables) {
	auto pair = statementToVariablesMap.find(statement);
	if (pair == statementToVariablesMap.end()) {
		statementToVariablesMap[statement] = variables;
	}
	else {
		pair->second.insert(variables.begin(), variables.end());
	}
}

void UsesStatementTable::addStatements(int statement, std::set<std::string> variables) {
	std::set<std::string>::iterator variable;
	for (variable = variables.begin(); variable != variables.end(); variable++) {
		auto pair = variableToStatementsMap.find(*variable);
		if (pair == variableToStatementsMap.end()) {
			variableToStatementsMap[*variable] = { statement };
		}
		else {
			pair->second.insert(statement);
		}
	}
}

void UsesStatementTable::flipStatementToVariables(std::unordered_map<int, std::set<std::string>> statementToVariables) {
	for (const auto& [key, values] : statementToVariables) {
		for (std::string value : values) {
			auto pair = variableToStatementsMap.find(value);
			if (pair == variableToStatementsMap.end()) {
				variableToStatementsMap[value] = { key };
			}
			else {
				pair->second.insert(key);
			}
		}
	}
}