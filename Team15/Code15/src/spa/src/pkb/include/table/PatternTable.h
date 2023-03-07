#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/include/models/Line.h"

class PatternTable {
public:
	PatternTable();

	void addAssignPattern(int assignStmtNum, std::string lhsVarName, std::set<std::vector<std::string>> rhsExprs);

	void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	void addAllWhileOrIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileOrIfLine);

	std::set<int> getAllStmts();

	std::string getVarFromStmt(int assignStmtNum);

	std::set<std::string> getVarsFromStmt(int whileOrIfStmtNum);

	std::set<int> getStmtsFromVar(std::string varName);

	std::set<std::vector<std::string>> getExprsFromStmt(int assignStmtNum);

	std::set<int> getStmtsFromExpr(std::vector<std::string> rhsExpr);

	std::set<std::vector<std::string>> getExprsFromVar(std::string lhsVarName);

	std::set<std::string> getVarsFromExpr(std::vector<std::string> rhsExpr);

	void addStmt(int stmtNum);

	void mapStmtToVar(int assignStmtNum, std::string lhsVarName);

	void mapStmtToVars(int whileOrIfStmtNum, std::string controlVarName);

	void mapVarToStmts(std::string varName, int stmtNum);

	void mapStmtToExprs(int assignStmtNum, std::set<std::vector<std::string>> rhsExprs);

	void mapStmtToOneExpr(int assignStmtNum, std::vector<std::string> rhsExpr);

	void mapExprToStmts(std::set<std::vector<std::string>> rhsExprs, int assignStmtNum);

	void mapOneExprToStmts(std::vector<std::string> rhsExpr, int assignStmtNum);

	void mapVarToExprs(std::string lhsVarName, std::set<std::vector<std::string>> rhsExprs);

	void mapVarToOneExpr(std::string lhsVarName, std::vector<std::string> rhsExpr);

	void mapExprToVars(std::set<std::vector<std::string>> rhsExprs, std::string lhsVarName);

	void mapOneExprToVars(std::vector<std::string> rhsExpr, std::string lhsVarName);

private:
	std::set<int> allStmtsSet;
	std::unordered_map<int, std::string> stmtToVarMap;
	std::unordered_map<int, std::set<std::string>> stmtToVarsMap;
	std::unordered_map<std::string, std::set<int>> varToStmtsMap;
	std::unordered_map<int, std::set<std::vector<std::string>>> stmtToExprsMap;
	std::map<std::vector<std::string>, std::set<int>> exprToStmtsMap;
	std::unordered_map<std::string, std::set<std::vector<std::string>>> varToExprsMap;
	std::map<std::vector<std::string>, std::set<std::string>> exprToVarsMap;
};
