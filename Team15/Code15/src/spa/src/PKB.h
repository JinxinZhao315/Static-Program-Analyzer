#pragma once

#include "Tokens.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "VariableTable.h"
#include "ConstantTable.h"
#include "FollowsTable.h"
#include "FollowsStarTable.h"

using namespace std;

class PKB {
public:
	PKB();

	void addProc(std::string procName);

	void addStmt(Tokens::Keyword stmtType, int stmtNum);

	void addVar(std::string varName);

	void addConst(std::string constVal);

	void addFollows(int leaderNum, int followerNum);

	void addFollowsStar(int leaderNum, std::set<int> followerNums);

	//void addParent(int parentNum, int childNum);

	//void addParentStar(int parentNum, std::set<int> childrenNums);

	std::set<std::string> getAllProcNames();

	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(Tokens::Keyword stmtType);

	std::set<std::string> getAllVarNames();

	std::set<std::string> getAllConstVals();

	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

	bool isFollowsEmpty();

private:
	ProcedureTable procTable;
	StatementTable stmtTable;
	VariableTable varTable;
	ConstantTable constTable;
	FollowsTable followsTable;
	FollowsStarTable followsStarTable;
	//AbstractionTable<int, int> parentTable;
	//AbstractionTable<int, int> parentStarTable;
};