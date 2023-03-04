#include "pkb/include/table/PatternTable.h"

PatternTable::PatternTable() = default;

void PatternTable::addAssignPattern(int assignStmtNum, std::string lhsVarName, std::set<std::vector<std::string>> rhsPostfixes) {
	mapStmtToVar(assignStmtNum, lhsVarName);
	mapVarToStmts(lhsVarName, assignStmtNum);
	mapStmtToPostfixes(assignStmtNum, rhsPostfixes);
	mapPostfixToStmts(rhsPostfixes, assignStmtNum);
	mapVarToPostfixes(lhsVarName, rhsPostfixes);
	mapPostfixToVars(rhsPostfixes, lhsVarName);
}

void PatternTable::addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
	for (const auto& [var, lines] : lhsVarToRhsLine) {
		for (Line line : lines) {
			int stmtNum = line.getLineNumber();
			std::vector<std::string> postfix = line.getTokens();
			mapStmtToVar(stmtNum, var);
			mapVarToStmts(var, stmtNum);
			mapStmtToOnePostfix(stmtNum, postfix);
			mapOnePostfixToStmts(postfix, stmtNum);
			mapVarToOnePostfix(var, postfix);
			mapOnePostfixToVars(postfix, var);
		}
	}
}

void PatternTable::addAllWhileOrIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileOrIfLine) {
	for (const auto& [var, lines] : controlVarToWhileOrIfLine) {
		for (Line line : lines) {
			int stmtNum = line.getLineNumber();
			addStmt(stmtNum);
			mapStmtToVars(stmtNum, var);
			mapVarToStmts(var, stmtNum);
		}
	}
}

std::set<int> PatternTable::getAllStmts() {
	return allStmtsSet;
}

std::string PatternTable::getVarFromStmt(int assignStmtNum) {
	auto pair = stmtToVarMap.find(assignStmtNum);
	if (pair == stmtToVarMap.end()) {
		return "0";
	}
	return pair->second;
}

std::set<std::string> PatternTable::getVarsFromStmt(int whileOrIfStmtNum) {
	auto pair = stmtToVarsMap.find(whileOrIfStmtNum);
	if (pair == stmtToVarsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> PatternTable::getStmtsFromVar(std::string varName) {
	auto pair = varToStmtsMap.find(varName);
	if (pair == varToStmtsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::vector<std::string>> PatternTable::getPostfixesFromStmt(int assignStmtNum) {
	auto pair = stmtToPostfixesMap.find(assignStmtNum);
	if (pair == stmtToPostfixesMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> PatternTable::getStmtsFromPostfix(std::vector<std::string> rhsPostfix) {
	auto pair = postfixToStmtsMap.find(rhsPostfix);
	if (pair == postfixToStmtsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::vector<std::string>> PatternTable::getPostfixesFromVar(std::string lhsVarName) {
	auto pair = varToPostfixesMap.find(lhsVarName);
	if (pair == varToPostfixesMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::string> PatternTable::getVarsFromPostfix(std::vector<std::string> rhsPostfix) {
	auto pair = postfixToVarsMap.find(rhsPostfix);
	if (pair == postfixToVarsMap.end()) {
		return {};
	}
	return pair->second;
}

void PatternTable::addStmt(int stmtNum) {
	allStmtsSet.insert(stmtNum);
}

void PatternTable::mapStmtToVar(int assignStmtNum, std::string lhsVarName) {
	stmtToVarMap[assignStmtNum] = lhsVarName;
}

void PatternTable::mapStmtToVars(int whileOrIfStmtNum, std::string controlVarName) {
	auto pair = stmtToVarsMap.find(whileOrIfStmtNum);
	if (pair == stmtToVarsMap.end()) {
		stmtToVarsMap[whileOrIfStmtNum] = { controlVarName };
	}
	else {
		pair->second.insert(controlVarName);
	}
}

void PatternTable::mapVarToStmts(std::string varName, int stmtNum) {
	auto pair = varToStmtsMap.find(varName);
	if (pair == varToStmtsMap.end()) {
		varToStmtsMap[varName] = { stmtNum };
	}
	else {
		pair->second.insert(stmtNum);
	}
}

void PatternTable::mapStmtToPostfixes(int assignStmtNum, std::set<std::vector<std::string>> rhsPostfixes) {
	auto pair = stmtToPostfixesMap.find(assignStmtNum);
	if (pair == stmtToPostfixesMap.end()) {
		stmtToPostfixesMap[assignStmtNum] = rhsPostfixes;
	}
	else {
		pair->second.insert(rhsPostfixes.begin(), rhsPostfixes.end());
	}
}

void PatternTable::mapStmtToOnePostfix(int assignStmtNum, std::vector<std::string> rhsPostfix) {
	auto pair = stmtToPostfixesMap.find(assignStmtNum);
	if (pair == stmtToPostfixesMap.end()) {
		stmtToPostfixesMap[assignStmtNum] = { rhsPostfix };
	}
	else {
		pair->second.insert(rhsPostfix);
	}
}

void PatternTable::mapPostfixToStmts(std::set<std::vector<std::string>> rhsPostfixes, int assignStmtNum) {
	for (std::vector<std::string> postfix : rhsPostfixes) {
		auto pair = postfixToStmtsMap.find(postfix);
		if (pair == postfixToStmtsMap.end()) {
			postfixToStmtsMap[postfix] = { assignStmtNum };
		}
		else {
			pair->second.insert(assignStmtNum);
		}
	}
}

void PatternTable::mapOnePostfixToStmts(std::vector<std::string> rhsPostfix, int assignStmtNum) {
	auto pair = postfixToStmtsMap.find(rhsPostfix);
	if (pair == postfixToStmtsMap.end()) {
		postfixToStmtsMap[rhsPostfix] = { assignStmtNum };
	}
	else {
		pair->second.insert(assignStmtNum);
	}
}

void PatternTable::mapVarToPostfixes(std::string lhsVarName, std::set<std::vector<std::string>> rhsPostfixes) {
	auto pair = varToPostfixesMap.find(lhsVarName);
	if (pair == varToPostfixesMap.end()) {
		varToPostfixesMap[lhsVarName] = rhsPostfixes;
	}
	else {
		pair->second.insert(rhsPostfixes.begin(), rhsPostfixes.end());
	}
}

void PatternTable::mapVarToOnePostfix(std::string lhsVarName, std::vector<std::string> rhsPostfix) {
	auto pair = varToPostfixesMap.find(lhsVarName);
	if (pair == varToPostfixesMap.end()) {
		varToPostfixesMap[lhsVarName] = { rhsPostfix };
	}
	else {
		pair->second.insert(rhsPostfix);
	}
}

void PatternTable::mapPostfixToVars(std::set<std::vector<std::string>> rhsPostfixes, std::string lhsVarName) {
	for (std::vector<std::string> postfix : rhsPostfixes) {
		auto pair = postfixToVarsMap.find(postfix);
		if (pair == postfixToVarsMap.end()) {
			postfixToVarsMap[postfix] = { lhsVarName };
		}
		else {
			pair->second.insert(lhsVarName);
		}
	}
}

void PatternTable::mapOnePostfixToVars(std::vector<std::string> rhsPostfix, std::string lhsVarName) {
	auto pair = postfixToVarsMap.find(rhsPostfix);
	if (pair == postfixToVarsMap.end()) {
		postfixToVarsMap[rhsPostfix] = { lhsVarName };
	}
	else {
		pair->second.insert(lhsVarName);
	}
}