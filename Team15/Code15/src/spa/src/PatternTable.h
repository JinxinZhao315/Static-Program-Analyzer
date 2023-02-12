#pragma once

#include <set>
#include <string>
#include <map>
#include <vector>

using namespace std;

class PatternTable {
public:
	PatternTable();

	void addPattern(int assignStmtNum, string lhsVarName, set<vector<string>> rhsPostfixes);

	string getVarFromStmt(int assignStmtNum);

	set<int> getStmtsFromVar(string lhsVarName);

	set<vector<string>> getPostfixesFromStmt(int assignStmtNum);

	set<int> getStmtsFromPostfix(vector<string> rhsPostfix);

	set<vector<string>> getPostfixesFromVar(string lhsVarName);

	set<string> getVarsFromPostfix(vector<string> rhsPostfix);

	void mapStmtToVar(int assignStmtNum, string lhsVarName);

	void mapVarToStmts(string lhsVarName, int assignStmtNum);

	void mapStmtToPostfixes(int assignStmtNum, set<vector<string>> rhsPostfixes);

	void mapPostfixToStmts(set<vector<string>> rhsPostfixes, int assignStmtNum);

	void mapVarToPostfixes(string lhsVarName, set<vector<string>> rhsPostfixes);

	void mapPostfixToVars(set<vector<string>> rhsPostfixes, string lhsVarName);

private:
	map<int, string> stmtToVarMap;
	map<string, set<int>> varToStmtsMap;
	map<int, set<vector<string>>> stmtToPostfixesMap;
	map<vector<string>, set<int>> postfixToStmtsMap;
	map<string, set<vector<string>>> varToPostfixesMap;
	map<vector<string>, set<string>> postfixToVarsMap;
};
