#pragma once

#include "EntityStorage.h"
#include "StatementTable.h"
#include "FollowsTable.h"
#include "FollowsStarTable.h"

using namespace std;

class PKB {
public:
	void addProc(std::string procName);

	void addStmt(int stmtNum, std::string stmtType);

	void addVar(std::string varName);

	void addConst(std::string constVal);

	void addFollows(int leaderNum, int followerNum);

	void addFollowsStar(int leaderNum, std::set<int> followerNums);

	std::set<std::string> getAllProcNames();

	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(std::string stmtType);

	std::set<std::string> getAllVarNames();

	std::set<std::string> getAllConstVals();

	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

private:
	EntityStorage<std::string> procTable;
	StatementTable stmtTable;
	StatementTable readTable;
	StatementTable printTable;
	StatementTable assignTable;
	StatementTable callTable;
	StatementTable whileTable;
	StatementTable ifTable;
	EntityStorage<std::string> varTable;
	EntityStorage<std::string> constTable;
	FollowsTable followsTable;
	FollowsStarTable followsStarTable;
};