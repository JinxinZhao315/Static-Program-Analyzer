#pragma once

#include "Tokens.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "VariableTable.h"
#include "ConstantTable.h"
#include "AbstractionTable.h"

using namespace std;

class PKB {
public:
	PKB();

	//SP procedure
	void addProc(std::string procName);

	//SP statement
	void addStmt(Tokens::Keyword stmtType, int stmtNum);

	//SP variable
	void addVar(std::string varName);

	//SP constant
	void addConst(std::string constVal);

	//SP follows
	void addFollows(int leaderNum, int followerNum);

	//SP follows*
	void addFollowsStar(int leaderNum, std::set<int> followerNums);

	//SP parent
	void addParent(int parentNum, int childNum);

	//SP parent*
	void addParentStar(int parentNum, std::set<int> childrenNums);

	//SP uses
	void addUsesStmt(int stmtNum, std::set<std::string> varNames);

	void addUsesProc(std::string procName, std::set<std::string> varNames);

	//SP modifies
	void addModifiesStmt(int stmtNum, std::set<std::string> varNames);

	void addModifiesProc(std::string procName, std::set<std::string> varNames);

	//QPS procedure
	std::set<std::string> getAllProcNames();

	//QPS statement
	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(Tokens::Keyword stmtType);

	//QPS variable
	std::set<std::string> getAllVarNames();

	//QPS constant
	std::set<std::string> getAllConstVals();

	//QPS follow
	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool isFollowsEmpty();

	//QPS follows*
	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

	//QPS parent
	int getParentParentNum(int childNum);

	int getParentChildNum(int parentNum);

	bool areInParentRelationship(int parentNum, int childNum);

	bool isParentEmpty();

	//QPS parent*
	std::set<int> getParentStarParentNums(int child);

	std::set<int> getParentStarChildNums(int parent);

	bool areInParentStarRelationship(int parentNum, int childNum);

	//QPS uses
	std::set<std::string> getUsesVarsFromStmt(int stmtNum);

	std::set<int> getUsesStmtsFromVar(std::string varName);

	std::set<std::string> getUsesVarsFromProc(std::string procName);

	std::set<std::string> getUsesProcsFromVar(std::string varName);
	
	bool areInUsesStmtRelationship(int stmtNum, std::string varName);

	bool areInUsesProcRelationship(std::string procName, std::string varName);

	//QPS modifies
	std::set<std::string> getModifiesVarsFromStmt(int stmtNum);

	std::set<int> getModifiesStmtsFromVar(std::string varName);

	std::set<std::string> getModifiesVarsFromProc(std::string procName);

	std::set<std::string> getModifiesProcsFromVar(std::string varName);

	bool areInModifiesStmtRelationship(int stmtNum, std::string varName);

	bool areInModifiesProcRelationship(std::string procName, std::string varName);

private:
	ProcedureTable procTable;
	StatementTable stmtTable;
	VariableTable varTable;
	ConstantTable constTable;
	AbstractionTable<int, int> followsTable;
	AbstractionTable<int, int> followsStarTable;
	AbstractionTable<int, int> parentTable;
	AbstractionTable<int, int> parentStarTable;
	AbstractionTable<int, std::string> usesStmtTable;
	AbstractionTable<std::string, std::string> usesProcTable;
	AbstractionTable<int, std::string> modifiesStmtTable;
	AbstractionTable<std::string, std::string> modifiesProcTable;
};