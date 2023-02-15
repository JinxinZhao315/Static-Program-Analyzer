#pragma once

#include <string>

#include "Tokens.h"
#include "EntityTable.h"
#include "StatementTable.h"
#include "AbstractionTable.h"
#include "PatternTable.h"

using namespace std;

class PKB {
public:
	PKB();

	//SP procedure
	void addProc(std::string procName);

	//SP variable
	void addVar(std::string varName);

	//SP constant
	void addConst(std::string constVal);

	//SP statement
	void addStmt(Tokens::Keyword stmtType, int stmtNum);

	//SP follows
	void addFollows(int leaderNum, int followerNum);

	//SP follows*
	void addFollowsStar(int leaderNum, std::set<int> followerNums);

	//SP parent
	void addParent(int parentNum, int childNum);

	//SP parent*
	void addParentStar(int parentNum, std::set<int> childrenNums);

	//SP uses statement-variable
	void addUsesStmt(int stmtNum, std::set<std::string> varNames);

	//SP uses procedure-variable
	void addUsesProc(std::string procName, std::set<std::string> varNames);

	//SP modifies statement-variable
	void addModifiesStmt(int stmtNum, std::set<std::string> varNames);

	//SP modifies procedure-variable
	void addModifiesProc(std::string procName, std::set<std::string> varNames);

	//SP pattern
	void addPattern(int assignStmtNum, string lhsVarName, set<vector<string>> rhsPostfixes);

	//QPS procedure
	std::set<std::string> getAllProcNames();

	//QPS variable
	std::set<std::string> getAllVarNames();

	//QPS constant
	std::set<std::string> getAllConstVals();

	//QPS statement
	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(Tokens::Keyword stmtType);

	//QPS follow
	int getFollowsLeaderNum(int followerNum);

	int getFollowsFollowerNum(int leaderNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool isFollowsEmpty();

	//QPS follows*
	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

	bool isFollowsStarEmpty();

	//QPS parent
	int getParentParentNum(int childNum);

	int getParentChildNum(int parentNum);

	bool areInParentRelationship(int parentNum, int childNum);

	bool isParentEmpty();

	//QPS parent*
	std::set<int> getParentStarParentNums(int child);

	std::set<int> getParentStarChildNums(int parent);

	bool areInParentStarRelationship(int parentNum, int childNum);

	bool isParentStarEmpty();

	//QPS uses statement-variable
	std::set<std::string> getUsesVarsFromStmt(int stmtNum);

	std::set<int> getUsesStmtsFromVar(std::string varName);

	bool areInUsesStmtRelationship(int stmtNum, std::string varName);

	//QPS uses procedure-variable
	std::set<std::string> getUsesVarsFromProc(std::string procName);

	std::set<std::string> getUsesProcsFromVar(std::string varName);

	bool areInUsesProcRelationship(std::string procName, std::string varName);

	//QPS modifies statement-variable
	std::set<std::string> getModifiesVarsFromStmt(int stmtNum);

	std::set<int> getModifiesStmtsFromVar(std::string varName);

	bool areInModifiesStmtRelationship(int stmtNum, std::string varName);

	//QPS modifies procedure-variable
	std::set<std::string> getModifiesVarsFromProc(std::string procName);

	std::set<std::string> getModifiesProcsFromVar(std::string varName);

	bool areInModifiesProcRelationship(std::string procName, std::string varName);

	//QPS pattern
	string getPatternVarFromStmt(int assignStmtNum);

	set<int> getPatternStmtsFromVar(string lhsVarName);

	set<vector<string>> getPatternPostfixesFromStmt(int assignStmtNum);

	set<int> getPatternStmtsFromPostfix(vector<string> rhsPostfix);

	set<vector<string>> getPatternPostfixesFromVar(string lhsVarName);

	set<string> getPatternVarsFromPostfix(vector<string> rhsPostfix);

private:
	EntityTable<std::string> procTable;
	EntityTable<std::string> varTable;
	EntityTable<std::string> constTable;
	StatementTable stmtTable;
	AbstractionTable<int, int> followsTable;
	AbstractionTable<int, int> followsStarTable;
	AbstractionTable<int, int> parentTable;
	AbstractionTable<int, int> parentStarTable;
	AbstractionTable<int, std::string> usesStmtTable;
	AbstractionTable<std::string, std::string> usesProcTable;
	AbstractionTable<int, std::string> modifiesStmtTable;
	AbstractionTable<std::string, std::string> modifiesProcTable;
	PatternTable patternTable;
};