#pragma once

#include "pkb/include/table/EntityTable.h"
#include "pkb/include/table/StatementTable.h"
#include "pkb/include/table/AbstractionTable.h"
#include "pkb/include/table/PatternTable.h"
#include <set>

using namespace std;

class PKB {
public:
	PKB();

	//SP procedure
	void addProc(std::string procName);

	void addAllProcs(std::set<std::string> procNames);

	//SP variable
	void addVar(std::string varName);

	void addAllVars(std::set<std::string> varNames);

	//SP constant
	void addConst(std::string constVal);

	void addAllConsts(std::set<std::string> constVals);

	//SP statement
	void addStmt(string stmtType, int stmtNum);

	void addAllStmts(std::set<int> stmtNums);

	void addAllStmtsByType(unordered_map<string, set<int>> stmtNumsByType);

	//SP follows
	void addFollows(int leaderNum, int followerNum);

	void addAllFollows(std::unordered_map<int, int> allLeaderToFollower);

	//SP follows*
	void addFollowsStar(int leaderNum, std::set<int> followerNums);

	void addAllFollowsStar(std::unordered_map<int, set<int>> allLeaderToFollowers);

	//SP parent
	void addParent(int parentNum, int childNum);

	void addAllParent(std::unordered_map<int, int> allParentToChild);

	//SP parent*
	void addParentStar(int parentNum, std::set<int> childrenNums);

	void addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren);

	//SP uses statement-variable
	void addUsesStmt(int stmtNum, std::set<std::string> varNames);

	void addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//SP uses procedure-variable
	void addUsesProc(std::string procName, std::set<std::string> varNames);

	void addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//SP modifies statement-variable
	void addModifiesStmt(int stmtNum, std::set<std::string> varNames);

	void addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//SP modifies procedure-variable
	void addModifiesProc(std::string procName, std::set<std::string> varNames);

	void addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//SP pattern
	void addPattern(int assignStmtNum, string lhsVarName, set<vector<string>> rhsPostfixes);

	void addAllPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	//QPS procedure
	std::set<std::string> getAllProcNames();

	//QPS variable
	std::set<std::string> getAllVarNames();

	//QPS constant
	std::set<std::string> getAllConstVals();

	//QPS statement
	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(string stmtType);

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