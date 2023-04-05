#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/include/models/Line.h"
#include "pkb/include/hasher/VectorHasher.h"

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
				mapStmtToExprs(stmtNum, expr);
				mapExprToStmts(expr, stmtNum);
				mapVarToExprs(var, expr);
				mapExprToVars(expr, var);
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

private:
	std::set<int> allStmtsSet;
	std::unordered_map<int, std::string> stmtToVarMap;
	std::unordered_map<int, std::set<std::string>> stmtToVarsMap;
	std::unordered_map<std::string, std::set<int>> varToStmtsMap;
	std::unordered_map<int, std::set<std::vector<std::string>>> stmtToExprsMap;
	std::unordered_map<std::vector<std::string>, std::set<int>, VectorHasher> exprToStmtsMap;
	std::unordered_map<std::string, std::set<std::vector<std::string>>> varToExprsMap;
	std::unordered_map<std::vector<std::string>, std::set<std::string>, VectorHasher> exprToVarsMap;

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

	inline void mapStmtToExprs(int assignStmtNum, std::vector<std::string> rhsExpr) {
		auto pair = stmtToExprsMap.find(assignStmtNum);
		if (pair == stmtToExprsMap.end()) {
			stmtToExprsMap[assignStmtNum] = { rhsExpr };
		}
		else {
			pair->second.insert(rhsExpr);
		}
	}

	inline void mapExprToStmts(std::vector<std::string> rhsExpr, int assignStmtNum) {
		auto pair = exprToStmtsMap.find(rhsExpr);
		if (pair == exprToStmtsMap.end()) {
			exprToStmtsMap[rhsExpr] = { assignStmtNum };
		}
		else {
			pair->second.insert(assignStmtNum);
		}
	}

	inline void mapVarToExprs(std::string lhsVarName, std::vector<std::string> rhsExpr) {
		auto pair = varToExprsMap.find(lhsVarName);
		if (pair == varToExprsMap.end()) {
			varToExprsMap[lhsVarName] = { rhsExpr };
		}
		else {
			pair->second.insert(rhsExpr);
		}
	}

	inline void mapExprToVars(std::vector<std::string> rhsExpr, std::string lhsVarName) {
		auto pair = exprToVarsMap.find(rhsExpr);
		if (pair == exprToVarsMap.end()) {
			exprToVarsMap[rhsExpr] = { lhsVarName };
		}
		else {
			pair->second.insert(lhsVarName);
		}
	}
};
