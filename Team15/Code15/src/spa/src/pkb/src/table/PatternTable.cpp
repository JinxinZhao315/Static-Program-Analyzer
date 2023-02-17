#include "pkb/include/table/PatternTable.h"

PatternTable::PatternTable() = default;

void PatternTable::addPattern(int assignStmtNum, string lhsVarName, set<vector<string>> rhsPostfixes) {
	mapStmtToVar(assignStmtNum, lhsVarName);
	mapVarToStmts(lhsVarName, assignStmtNum);
	mapStmtToPostfixes(assignStmtNum, rhsPostfixes);
	mapPostfixToStmts(rhsPostfixes, assignStmtNum);
	mapVarToPostfixes(lhsVarName, rhsPostfixes);
	mapPostfixToVars(rhsPostfixes, lhsVarName);
}

string PatternTable::getVarFromStmt(int assignStmtNum) {
	auto pair = stmtToVarMap.find(assignStmtNum);
	if (pair == stmtToVarMap.end()) {
		return "0";
	}
	return pair->second;
}

set<int> PatternTable::getStmtsFromVar(string lhsVarName) {
	auto pair = varToStmtsMap.find(lhsVarName);
	if (pair == varToStmtsMap.end()) {
		return {};
	}
	return pair->second;
}

set<vector<string>> PatternTable::getPostfixesFromStmt(int assignStmtNum) {
	auto pair = stmtToPostfixesMap.find(assignStmtNum);
	if (pair == stmtToPostfixesMap.end()) {
		return {};
	}
	return pair->second;
}

set<int> PatternTable::getStmtsFromPostfix(vector<string> rhsPostfix) {
	auto pair = postfixToStmtsMap.find(rhsPostfix);
	if (pair == postfixToStmtsMap.end()) {
		return {};
	}
	return pair->second;
}

set<vector<string>> PatternTable::getPostfixesFromVar(string lhsVarName) {
	auto pair = varToPostfixesMap.find(lhsVarName);
	if (pair == varToPostfixesMap.end()) {
		return {};
	}
	return pair->second;
}

set<string> PatternTable::getVarsFromPostfix(vector<string> rhsPostfix) {
	auto pair = postfixToVarsMap.find(rhsPostfix);
	if (pair == postfixToVarsMap.end()) {
		return {};
	}
	return pair->second;
}

void PatternTable::mapStmtToVar(int assignStmtNum, string lhsVarName) {
	stmtToVarMap[assignStmtNum] = lhsVarName;
}

void PatternTable::mapVarToStmts(string lhsVarName, int assignStmtNum) {
	auto pair = varToStmtsMap.find(lhsVarName);
	if (pair == varToStmtsMap.end()) {
		varToStmtsMap[lhsVarName] = { assignStmtNum };
	}
	else {
		pair->second.insert(assignStmtNum);
	}
}

void PatternTable::mapStmtToPostfixes(int assignStmtNum, set<vector<string>> rhsPostfixes) {
	auto pair = stmtToPostfixesMap.find(assignStmtNum);
	if (pair == stmtToPostfixesMap.end()) {
		stmtToPostfixesMap[assignStmtNum] = rhsPostfixes;
	}
	else {
		pair->second.insert(rhsPostfixes.begin(), rhsPostfixes.end());
	}
}

void PatternTable::mapPostfixToStmts(set<vector<string>> rhsPostfixes, int assignStmtNum) {
	for (vector<string> postfix : rhsPostfixes) {
		auto pair = postfixToStmtsMap.find(postfix);
		if (pair == postfixToStmtsMap.end()) {
			postfixToStmtsMap[postfix] = { assignStmtNum };
		}
		else {
			pair->second.insert(assignStmtNum);
		}
	}
}

void PatternTable::mapVarToPostfixes(string lhsVarName, set<vector<string>> rhsPostfixes) {
	auto pair = varToPostfixesMap.find(lhsVarName);
	if (pair == varToPostfixesMap.end()) {
		varToPostfixesMap[lhsVarName] = rhsPostfixes;
	}
	else {
		pair->second.insert(rhsPostfixes.begin(), rhsPostfixes.end());
	}
}

void PatternTable::mapPostfixToVars(set<vector<string>> rhsPostfixes, string lhsVarName) {
	for (vector<string> postfix : rhsPostfixes) {
		auto pair = postfixToVarsMap.find(postfix);
		if (pair == postfixToVarsMap.end()) {
			postfixToVarsMap[postfix] = { lhsVarName };
		}
		else {
			pair->second.insert(lhsVarName);
		}
	}
}