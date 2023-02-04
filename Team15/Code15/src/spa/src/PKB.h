#pragma once

#include "EntityTable.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "VariableTable.h"
#include "ConstantTable.h"
#include "AbstractionTable.h"

using namespace std;

class PKB {
public:
	void addProc(std::string procName);

	void addStmt(int stmtNum, std::string stmtType);

	void addVar(std::string varName);

	void addConst(std::string constVal);

	void addFollows(int leaderNum, int followerNum);

	void addFollowsStar(int leaderNum, std::vector<int> followerNums);

	std::set<std::string> getAllProcNames();

	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(std::string stmtType);

	std::set<std::string> getAllVarNames();

	std::set<std::string> getAllConstVals();

	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	std::unordered_set<int> getFollowsStarLeaderNums(int followerNum);

	std::unordered_set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

private:
	EntityTable procTable;
	StatementTable stmtTable;
	StatementTable readTable;
	StatementTable printTable;
	StatementTable assignTable;
	StatementTable callTable;
	StatementTable whileTable;
	StatementTable ifTable;
	EntityTable varTable;
	EntityTable constTable;
};