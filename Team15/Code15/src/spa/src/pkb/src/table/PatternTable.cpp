#include "pkb/include/table/PatternTable.h"

PatternTable::PatternTable() = default;

void PatternTable::addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
	for (const auto& [var, lines] : lhsVarToRhsLine) {
		for (Line line : lines) {
			int stmtNum = line.getLineNumber();
			std::vector<std::string> expr = line.getTokens();
			mapStmtToVar(stmtNum, var);
			mapVarToStmts(var, stmtNum);
			mapStmtToOneExpr(stmtNum, expr);
			mapOneExprToStmts(expr, stmtNum);
			mapVarToOneExpr(var, expr);
			mapOneExprToVars(expr, var);
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

std::set<std::vector<std::string>> PatternTable::getExprsFromStmt(int assignStmtNum) {
	auto pair = stmtToExprsMap.find(assignStmtNum);
	if (pair == stmtToExprsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> PatternTable::getStmtsFromExpr(std::vector<std::string> rhsExpr) {
	auto pair = exprToStmtsMap.find(rhsExpr);
	if (pair == exprToStmtsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::vector<std::string>> PatternTable::getExprsFromVar(std::string lhsVarName) {
	auto pair = varToExprsMap.find(lhsVarName);
	if (pair == varToExprsMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<std::string> PatternTable::getVarsFromExpr(std::vector<std::string> rhsExpr) {
	auto pair = exprToVarsMap.find(rhsExpr);
	if (pair == exprToVarsMap.end()) {
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

void PatternTable::mapStmtToExprs(int assignStmtNum, std::set<std::vector<std::string>> rhsExprs) {
	auto pair = stmtToExprsMap.find(assignStmtNum);
	if (pair == stmtToExprsMap.end()) {
		stmtToExprsMap[assignStmtNum] = rhsExprs;
	}
	else {
		pair->second.insert(rhsExprs.begin(), rhsExprs.end());
	}
}

void PatternTable::mapStmtToOneExpr(int assignStmtNum, std::vector<std::string> rhsExpr) {
	auto pair = stmtToExprsMap.find(assignStmtNum);
	if (pair == stmtToExprsMap.end()) {
		stmtToExprsMap[assignStmtNum] = { rhsExpr };
	}
	else {
		pair->second.insert(rhsExpr);
	}
}

void PatternTable::mapExprToStmts(std::set<std::vector<std::string>> rhsExprs, int assignStmtNum) {
	for (std::vector<std::string> expr : rhsExprs) {
		auto pair = exprToStmtsMap.find(expr);
		if (pair == exprToStmtsMap.end()) {
			exprToStmtsMap[expr] = { assignStmtNum };
		}
		else {
			pair->second.insert(assignStmtNum);
		}
	}
}

void PatternTable::mapOneExprToStmts(std::vector<std::string> rhsExpr, int assignStmtNum) {
	auto pair = exprToStmtsMap.find(rhsExpr);
	if (pair == exprToStmtsMap.end()) {
		exprToStmtsMap[rhsExpr] = { assignStmtNum };
	}
	else {
		pair->second.insert(assignStmtNum);
	}
}

void PatternTable::mapVarToExprs(std::string lhsVarName, std::set<std::vector<std::string>> rhsExprs) {
	auto pair = varToExprsMap.find(lhsVarName);
	if (pair == varToExprsMap.end()) {
		varToExprsMap[lhsVarName] = rhsExprs;
	}
	else {
		pair->second.insert(rhsExprs.begin(), rhsExprs.end());
	}
}

void PatternTable::mapVarToOneExpr(std::string lhsVarName, std::vector<std::string> rhsExpr) {
	auto pair = varToExprsMap.find(lhsVarName);
	if (pair == varToExprsMap.end()) {
		varToExprsMap[lhsVarName] = { rhsExpr };
	}
	else {
		pair->second.insert(rhsExpr);
	}
}

void PatternTable::mapExprToVars(std::set<std::vector<std::string>> rhsExprs, std::string lhsVarName) {
	for (std::vector<std::string> expr : rhsExprs) {
		auto pair = exprToVarsMap.find(expr);
		if (pair == exprToVarsMap.end()) {
			exprToVarsMap[expr] = { lhsVarName };
		}
		else {
			pair->second.insert(lhsVarName);
		}
	}
}

void PatternTable::mapOneExprToVars(std::vector<std::string> rhsExpr, std::string lhsVarName) {
	auto pair = exprToVarsMap.find(rhsExpr);
	if (pair == exprToVarsMap.end()) {
		exprToVarsMap[rhsExpr] = { lhsVarName };
	}
	else {
		pair->second.insert(lhsVarName);
	}
}