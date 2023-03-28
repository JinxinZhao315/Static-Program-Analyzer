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

	//SP calls
	void addAllCalls(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//SP calls*
	void addAllCallsStar(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//SP next
	void addAllNext(std::unordered_map<int, std::set<int>> allPreviousToNexts);

	//SP next*
	void addAllNextStar(std::unordered_map<int, std::set<int>> allPreviousToNexts);

	//SP affects
	void addAllAffects(std::unordered_map<int, std::set<int>> allModifierToUsers);

	//SP affects*
	void addAllAffectsStar(std::unordered_map<int, std::set<int>> allModifierToUsers);

	//SP with read
	void addAllWithRead(unordered_map<int, std::string> readLineNumToVarName);

	//SP with print
	void addAllWithPrint(unordered_map<int, std::string> printLineNumToVarName);

	//SP with call
	void addAllWithCall(unordered_map<int, std::string> callLineNumToProcName);

	//SP assign pattern
	void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	//SP while pattern
	void addAllWhilePatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileLine);

	//SP if pattern
	void addAllIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToIfLine);

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
	int getFollowsLeaderNum(int followerNum, int invalidLeaderNum);

	int getFollowsFollowerNum(int leaderNum, int invalidFollowerNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool isFollowsEmpty();

	bool isFollowsLeaderEmpty();

	bool isFollowsFollowerEmpty();

	//QPS follows*
	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

	bool isFollowsStarEmpty();

	bool isFollowsStarLeaderEmpty();

	bool isFollowsStarFollowerEmpty();

	//QPS parent
	int getParentParentNum(int childNum, int invalidParentNum);

	std::set<int> getParentChildNums(int parentNum);

	bool areInParentRelationship(int parentNum, int childNum);

	bool isParentEmpty();

	bool isParentParentEmpty();

	bool isParentChildEmpty();

	//QPS parent*
	std::set<int> getParentStarParentNums(int childNum);

	std::set<int> getParentStarChildNums(int parentNum);

	bool areInParentStarRelationship(int parentNum, int childNum);

	bool isParentStarEmpty();

	bool isParentStarParentEmpty();

	bool isParentStarChildEmpty();

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

	//QPS calls
	std::set<std::string> getCallsCallerNames(std::string calleeName);

	std::set<std::string> getCallsCalleeNames(std::string callerName);

	bool areInCallsRelationship(std::string callerName, std::string calleeName);

	bool isCallsEmpty();

	bool isCallsCallerEmpty();

	bool isCallsCalleeEmpty();

	//QPS calls*
	std::set<std::string> getCallsStarCallerNames(std::string calleeName);

	std::set<std::string> getCallsStarCalleeNames(std::string callerName);

	bool areInCallsStarRelationship(std::string callerName, std::string calleeName);

	bool isCallsStarEmpty();

	bool isCallsStarCallerEmpty();

	bool isCallsStarCalleeEmpty();

	//QPS next
	std::set<int> getPreviousStmtNums(int nextStmtNum);

	std::set<int> getNextStmtNums(int previousStmtNum);

	bool areInNextRelationship(int previousStmtNum, int nextStmtNum);

	bool isNextEmpty();

	bool isPreviousStmtEmpty();

	bool isNextStmtEmpty();

	//QPS next*
	std::set<int> getStarPreviousStmtNums(int nextStmtNum);

	std::set<int> getStarNextStmtNums(int previousStmtNum);

	bool areInNextStarRelationship(int previousStmtNum, int nextStmtNum);

	bool isNextStarEmpty();

	bool isStarPreviousStmtEmpty();

	bool isStarNextStmtEmpty();

	void clearNextStar();

	//QPS affects
	std::set<int> getAffectsModifierStmtNums(int userStmtNum);

	std::set<int> getAffectsUserStmtNums(int modifierStmtNum);

	bool areInAffectsRelationship(int modifierStmtNum, int userStmtNum);

	bool isAffectsEmpty();

	bool isAffectsModifierStmtEmpty();

	bool isAffectsUserStmtEmpty();

	void clearAffects();

	//QPS affects*
	std::set<int> getAffectsStarModifierStmtNums(int userStmtNum);

	std::set<int> getAffectsStarUserStmtNums(int modifierStmtNum);

	bool areInAffectsStarRelationship(int modifierStmtNum, int userStmtNum);

	bool isAffectsStarEmpty();

	bool isAffectsStarModifierStmtEmpty();

	bool isAffectsStarUserStmtEmpty();

	void clearAffectsStar();

	//QPS with read
	std::string getWithReadVarName(int readLineNum, std::string invalidVarName);

	//QPS with print
	std::string getWithPrintVarName(int printLineNum, std::string invalidVarName);

	//QPS with call
	std::string getWithCallProcName(int callLineNum, std::string invalidProcName);

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
	RelationshipTable<std::string, std::string> callsTable;
	RelationshipTable<std::string, std::string> callsStarTable;
	RelationshipTable<int, int> nextTable;
	RelationshipTable<int, int> nextStarTable;
	RelationshipTable<int, int> affectsTable;
	RelationshipTable<int, int> affectsStarTable;
	RelationshipTable<int, std::string> withReadTable;
	RelationshipTable<int, std::string> withPrintTable;
	RelationshipTable<int, std::string> withCallTable;
	PatternTable assignPatternTable;
	PatternTable whilePatternTable;
	PatternTable ifPatternTable;
};
