#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "ProcedureTable.h"
#include "StatementTable.h"
#include "VariableTable.h"
#include "ConstantTable.h"
#include "AbstractionTable.h"

using namespace std;

class PKB {
public:
	void addProc(std::string procName);

	void addStmt(std::string stmtType, int stmtNum);

	void addVar(std::string varName);

	void addConst(std::string constVal);

	void addFollows(int leaderNum, int followerNum);

	void addFollowsStar(int leaderNum, std::vector<int> followerNums);

	std::unordered_set<std::string> getAllProcNames();

	std::unordered_set<int> getAllStmtNums();

	std::unordered_set<int> getAllStmtNumsByType(std::string stmtType);

	std::string getStmtType(int stmtNum);

	std::unordered_set<std::string> getAllVarNames();

	std::vector<std::string> getAllConstVals();

	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	std::unordered_set<int> getFollowsStarLeaderNums(int followerNum);

	std::unordered_set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

private:
	ProcedureTable procTable;
	StatementTable stmtTable;
	VariableTable varTable;
	ConstantTable constTable;
};