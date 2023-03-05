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

	void addAssignPattern(int assignStmtNum, std::string lhsVarName, std::set<std::vector<std::string>> rhsPostfixes);

	void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	void addAllWhileOrIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileOrIfLine);

	std::set<int> getAllStmts();

	std::string getVarFromStmt(int assignStmtNum);

	std::set<std::string> getVarsFromStmt(int whileOrIfStmtNum);

	std::set<int> getStmtsFromVar(std::string varName);

	std::set<std::vector<std::string>> getPostfixesFromStmt(int assignStmtNum);

	std::set<int> getStmtsFromPostfix(std::vector<std::string> rhsPostfix);

	std::set<std::vector<std::string>> getPostfixesFromVar(std::string lhsVarName);

	std::set<std::string> getVarsFromPostfix(std::vector<std::string> rhsPostfix);

	void addStmt(int stmtNum);

	void mapStmtToVar(int assignStmtNum, std::string lhsVarName);

	void mapStmtToVars(int whileOrIfStmtNum, std::string controlVarName);

	void mapVarToStmts(std::string varName, int stmtNum);

	void mapStmtToPostfixes(int assignStmtNum, std::set<std::vector<std::string>> rhsPostfixes);

	void mapStmtToOnePostfix(int assignStmtNum, std::vector<std::string> rhsPostfix);

	void mapPostfixToStmts(std::set<std::vector<std::string>> rhsPostfixes, int assignStmtNum);

	void mapOnePostfixToStmts(std::vector<std::string> rhsPostfix, int assignStmtNum);

	void mapVarToPostfixes(std::string lhsVarName, std::set<std::vector<std::string>> rhsPostfixes);

	void mapVarToOnePostfix(std::string lhsVarName, std::vector<std::string> rhsPostfix);

	void mapPostfixToVars(std::set<std::vector<std::string>> rhsPostfixes, std::string lhsVarName);

	void mapOnePostfixToVars(std::vector<std::string> rhsPostfix, std::string lhsVarName);

private:
	std::set<int> allStmtsSet;
	std::map<int, std::string> stmtToVarMap;
	std::map<int, std::set<std::string>> stmtToVarsMap;
	std::map<std::string, std::set<int>> varToStmtsMap;
	std::map<int, std::set<std::vector<std::string>>> stmtToPostfixesMap;
	std::map<std::vector<std::string>, std::set<int>> postfixToStmtsMap;
	std::map<std::string, std::set<std::vector<std::string>>> varToPostfixesMap;
	std::map<std::vector<std::string>, std::set<std::string>> postfixToVarsMap;
};
