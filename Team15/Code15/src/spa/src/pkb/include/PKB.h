#pragma once

#include "pkb/include/table/RelationshipTable.h"
#include "pkb/include/table/EntityTable.h"
#include "pkb/include/table/PatternTable.h"
#include "pkb/include/table/StatementTable.h"

class PKB {
public:
	PKB();

	//SP procedure
	void addAllProcs(std::set<std::string> procNames);

	//SP variable
	void addAllVars(std::set<std::string> varNames);

	//SP constant
	void addAllConsts(std::set<std::string> constVals);

	//SP statement
	void addAllStmts(std::unordered_map<std::string, std::set<int>> stmtNums);

	//SP follows
	void addAllFollows(std::unordered_map<int, int> allLeaderToFollower);

	//SP follows*
	void addAllFollowsStar(std::unordered_map<int, std::set<int>> allLeaderToFollowers);

	//SP parent
	void addAllParent(std::unordered_map<int, std::set<int>> allParentToChildren);

	//SP parent*
	void addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren);

	//SP uses statement-variable
	void addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//SP uses procedure-variable
	void addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//SP modifies statement-variable
	void addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//SP modifies procedure-variable
	void addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//SP assign pattern
	void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	//SP while pattern
	void addAllWhilePatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileLine);

	//SP if pattern
	void addAllIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToIfLine);

	//SP calls
	void addAllCalls(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//SP calls*
	void addAllCallsStar(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//QPS procedure
	std::set<std::string> getAllProcNames();

	//QPS variable
	std::set<std::string> getAllVarNames();

	//QPS constant
	std::set<std::string> getAllConstVals();

	//QPS statement
	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(std::string stmtType);

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

	std::set<int> getParentChildrenNum(int parentNum);

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

	//QPS assign pattern
	std::string getAssignVarFromStmt(int assignStmtNum);

	std::set<int> getAssignStmtsFromVar(std::string lhsVarName);

	std::set<std::vector<std::string>> getAssignExprsFromStmt(int assignStmtNum);

	std::set<int> getAssignStmtsFromExpr(std::vector<std::string> rhsExpr);

	std::set<std::vector<std::string>> getAssignExprsFromVar(std::string lhsVarName);

	std::set<std::string> getAssignVarsFromExpr(std::vector<std::string> rhsExpr);

	//QPS while pattern
	std::set<int> getWhileStmtsWithVars();
	
	std::set<int> getWhileStmtsFromVar(std::string controlVarName);

	std::set<std::string> getWhileVarsFromStmt(int whileStmtNum);

	//QPS if pattern
	std::set<int> getIfStmtsWithVars();

	std::set<int> getIfStmtsFromVar(std::string controlVarName);

	std::set<std::string> getIfVarsFromStmt(int ifStmtNum);

	//QPS calls
	std::set<std::string> getCallsCallerNames(std::string calleeName);

	std::set<std::string> getCallsCalleeNames(std::string callerName);

	bool areInCallsRelationship(std::string callerName, std::string calleeName);

	bool isCallsEmpty();

	//QPS calls*
	std::set<std::string> getCallsStarCallerNames(std::string calleeName);

	std::set<std::string> getCallsStarCalleeNames(std::string callerName);

	bool areInCallsStarRelationship(std::string callerName, std::string calleeName);

	bool isCallsStarEmpty();

private:
	EntityTable<std::string> procTable;
	EntityTable<std::string> varTable;
	EntityTable<std::string> constTable;
	StatementTable stmtTable;
	RelationshipTable<int, int> followsTable;
	RelationshipTable<int, int> followsStarTable;
	RelationshipTable<int, int> parentTable;
	RelationshipTable<int, int> parentStarTable;
	RelationshipTable<int, std::string> usesStmtTable;
	RelationshipTable<std::string, std::string> usesProcTable;
	RelationshipTable<int, std::string> modifiesStmtTable;
	RelationshipTable<std::string, std::string> modifiesProcTable;
	PatternTable assignPatternTable;
	PatternTable whilePatternTable;
	PatternTable ifPatternTable;
	RelationshipTable<std::string, std::string> callsTable;
	RelationshipTable<std::string, std::string> callsStarTable;
};