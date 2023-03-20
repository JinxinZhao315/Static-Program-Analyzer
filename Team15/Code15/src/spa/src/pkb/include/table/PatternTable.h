#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/include/models/Line.h"

class PatternTable {
public:
	inline PatternTable() = default;

	inline void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
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

	inline void addAllWhileOrIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileOrIfLine) {
		for (const auto& [var, lines] : controlVarToWhileOrIfLine) {
			for (Line line : lines) {
				int stmtNum = line.getLineNumber();
				addStmt(stmtNum);
				mapStmtToVars(stmtNum, var);
				mapVarToStmts(var, stmtNum);
			}
		}
	}

	inline std::set<int> getAllStmts() {
		return allStmtsSet;
	}

	inline std::string getVarFromStmt(int assignStmtNum) {
		auto pair = stmtToVarMap.find(assignStmtNum);
		if (pair == stmtToVarMap.end()) {
			return "0";
		}
		return pair->second;
	}

	inline std::set<std::string> getVarsFromStmt(int whileOrIfStmtNum) {
		auto pair = stmtToVarsMap.find(whileOrIfStmtNum);
		if (pair == stmtToVarsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<int> getStmtsFromVar(std::string varName) {
		auto pair = varToStmtsMap.find(varName);
		if (pair == varToStmtsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<std::vector<std::string>> getExprsFromStmt(int assignStmtNum) {
		auto pair = stmtToExprsMap.find(assignStmtNum);
		if (pair == stmtToExprsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<int> getStmtsFromExpr(std::vector<std::string> rhsExpr) {
		auto pair = exprToStmtsMap.find(rhsExpr);
		if (pair == exprToStmtsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<std::vector<std::string>> getExprsFromVar(std::string lhsVarName) {
		auto pair = varToExprsMap.find(lhsVarName);
		if (pair == varToExprsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<std::string> getVarsFromExpr(std::vector<std::string> rhsExpr) {
		auto pair = exprToVarsMap.find(rhsExpr);
		if (pair == exprToVarsMap.end()) {
			return {};
		}
		return pair->second;
	}

private:
	std::set<int> allStmtsSet;
	std::unordered_map<int, std::string> stmtToVarMap;
	std::unordered_map<int, std::set<std::string>> stmtToVarsMap;
	std::unordered_map<std::string, std::set<int>> varToStmtsMap;
	std::unordered_map<int, std::set<std::vector<std::string>>> stmtToExprsMap;
	std::map<std::vector<std::string>, std::set<int>> exprToStmtsMap;
	std::unordered_map<std::string, std::set<std::vector<std::string>>> varToExprsMap;
	std::map<std::vector<std::string>, std::set<std::string>> exprToVarsMap;

	inline void addStmt(int stmtNum) {
		allStmtsSet.insert(stmtNum);
	}

	inline void mapStmtToVar(int assignStmtNum, std::string lhsVarName) {
		stmtToVarMap[assignStmtNum] = lhsVarName;
	}

	inline void mapStmtToVars(int whileOrIfStmtNum, std::string controlVarName) {
		auto pair = stmtToVarsMap.find(whileOrIfStmtNum);
		if (pair == stmtToVarsMap.end()) {
			stmtToVarsMap[whileOrIfStmtNum] = { controlVarName };
		}
		else {
			pair->second.insert(controlVarName);
		}
	}

	inline void mapVarToStmts(std::string varName, int stmtNum) {
		auto pair = varToStmtsMap.find(varName);
		if (pair == varToStmtsMap.end()) {
			varToStmtsMap[varName] = { stmtNum };
		}
		else {
			pair->second.insert(stmtNum);
		}
	}

	inline void mapStmtToExprs(int assignStmtNum, std::set<std::vector<std::string>> rhsExprs) {
		auto pair = stmtToExprsMap.find(assignStmtNum);
		if (pair == stmtToExprsMap.end()) {
			stmtToExprsMap[assignStmtNum] = rhsExprs;
		}
		else {
			pair->second.insert(rhsExprs.begin(), rhsExprs.end());
		}
	}

	inline void mapStmtToOneExpr(int assignStmtNum, std::vector<std::string> rhsExpr) {
		auto pair = stmtToExprsMap.find(assignStmtNum);
		if (pair == stmtToExprsMap.end()) {
			stmtToExprsMap[assignStmtNum] = { rhsExpr };
		}
		else {
			pair->second.insert(rhsExpr);
		}
	}

	inline void mapExprToStmts(std::set<std::vector<std::string>> rhsExprs, int assignStmtNum) {
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

	inline void mapOneExprToStmts(std::vector<std::string> rhsExpr, int assignStmtNum) {
		auto pair = exprToStmtsMap.find(rhsExpr);
		if (pair == exprToStmtsMap.end()) {
			exprToStmtsMap[rhsExpr] = { assignStmtNum };
		}
		else {
			pair->second.insert(assignStmtNum);
		}
	}

	inline void mapVarToExprs(std::string lhsVarName, std::set<std::vector<std::string>> rhsExprs) {
		auto pair = varToExprsMap.find(lhsVarName);
		if (pair == varToExprsMap.end()) {
			varToExprsMap[lhsVarName] = rhsExprs;
		}
		else {
			pair->second.insert(rhsExprs.begin(), rhsExprs.end());
		}
	}

	inline void mapVarToOneExpr(std::string lhsVarName, std::vector<std::string> rhsExpr) {
		auto pair = varToExprsMap.find(lhsVarName);
		if (pair == varToExprsMap.end()) {
			varToExprsMap[lhsVarName] = { rhsExpr };
		}
		else {
			pair->second.insert(rhsExpr);
		}
	}

	inline void mapExprToVars(std::set<std::vector<std::string>> rhsExprs, std::string lhsVarName) {
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

	inline void mapOneExprToVars(std::vector<std::string> rhsExpr, std::string lhsVarName) {
		auto pair = exprToVarsMap.find(rhsExpr);
		if (pair == exprToVarsMap.end()) {
			exprToVarsMap[rhsExpr] = { lhsVarName };
		}
		else {
			pair->second.insert(lhsVarName);
		}
	}
};
