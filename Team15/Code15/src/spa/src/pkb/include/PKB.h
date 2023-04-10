#pragma once

#include "pkb/include/table/RelationshipTable.h"
#include "pkb/include/table/EntityTable.h"
#include "pkb/include/table/PatternTable.h"
#include "pkb/include/table/StatementTable.h"
#include "sp/include/SourceProcessor.h"
#include "pkb/include/hasher/PairHasher.h"

class SourceProcessor;

class PKB {
public:
	PKB();

	//ADD
	//add procedure
	void addAllProcs(std::set<std::string> procNames);

	//add variable
	void addAllVars(std::set<std::string> varNames);

	//add constant
	void addAllConsts(std::set<std::string> constVals);

	//add line
	void addAllLines(std::vector<Line> allLines);

	//add statement
	void addAllStmts(std::unordered_map<KeywordsEnum, std::set<int>> stmtNums);

	//add follows
	void addAllFollows(std::unordered_map<int, int> allLeaderToFollower);

	//add follows*
	void addAllFollowsStar(std::unordered_map<int, std::set<int>> allLeaderToFollowers);

	//add parent
	void addAllParent(std::unordered_map<int, std::set<int>> allParentToChildren);

	//add parent*
	void addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren);

	//add uses statement-variable
	void addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//add uses procedure-variable
	void addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//add modifies statement-variable
	void addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars);

	//add modifies procedure-variable
	void addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars);

	//add calls
	void addAllCalls(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//add calls*
	void addAllCallsStar(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees);

	//add next
	void addAllNext(std::unordered_map<int, std::set<int>> allPreviousToNexts);

	//add next*
	void addAllNextStar(std::unordered_map<int, std::set<int>> allPreviousToNexts);

	//add affects
	void addAffectsModifierToUsers(int modifier, std::set<int> users);

	void addAffectsUserToModifiers(int user, std::set<int> modifiers);

	void addAllAffects(std::unordered_map<int, std::set<int>> allModifierToUsers);

	//add affects*
	void addAffectsStarModifierToUsers(int modifier, std::set<int> users);

	void addAffectsStarUserToModifiers(int user, std::set<int> modifiers);

	void addAllAffectsStar(std::unordered_map<int, std::set<int>> allModifierToUsers);

	//add with (read)
	void addAllWithRead(unordered_map<int, std::string> readLineNumToVarName);

	//add with (print)
	void addAllWithPrint(unordered_map<int, std::string> printLineNumToVarName);

	//add with (call)
	void addAllWithCall(unordered_map<int, std::string> callLineNumToProcName);

	//add assign pattern
	void addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine);

	//add while pattern
	void addAllWhilePatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileLine);

	//add if pattern
	void addAllIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToIfLine);

	//add cache
	void addCache(std::unordered_map<std::pair<int, int>, bool, PairHasher<int, int>> cache);

	//GET
	//get procedure
	std::set<std::string> getAllProcNames();

	//get variable
	std::set<std::string> getAllVarNames();

	//get constant
	std::set<std::string> getAllConstVals();

	//get line
	std::vector<Line> getAllLines();

	std::unordered_map<int, Line> getStmtNumToLineMap();

	//get statement
	std::set<int> getAllStmtNums();

	std::set<int> getAllStmtNumsByType(KeywordsEnum stmtType);

	//get follows
	int getFollowsLeaderNum(int followerNum, int invalidLeaderNum);

	int getFollowsFollowerNum(int leaderNum, int invalidFollowerNum);

	bool areInFollowsRelationship(int leaderNum, int followerNum);

	bool isFollowsEmpty();

	//get follows*
	std::set<int> getFollowsStarLeaderNums(int followerNum);

	std::set<int> getFollowsStarFollowerNums(int leaderNum);

	bool areInFollowsStarRelationship(int leaderNum, int followerNum);

	bool isFollowsStarEmpty();

	//get parent
	int getParentParentNum(int childNum, int invalidParentNum);

	std::set<int> getParentChildNums(int parentNum);

	bool areInParentRelationship(int parentNum, int childNum);

	bool isParentEmpty();

	//get parent*
	std::set<int> getParentStarParentNums(int childNum);

	std::set<int> getParentStarChildNums(int parentNum);

	bool areInParentStarRelationship(int parentNum, int childNum);

	bool isParentStarEmpty();

	//get uses statement-variable
	std::unordered_map<int, std::set<std::string>> getStmtUsesVarsMap();
	
	std::set<std::string> getUsesVarsFromStmt(int stmtNum);

	std::set<int> getUsesStmtsFromVar(std::string varName);

	bool areInUsesStmtRelationship(int stmtNum, std::string varName);

	//get uses procedure-variable
	std::set<std::string> getUsesVarsFromProc(std::string procName);

	std::set<std::string> getUsesProcsFromVar(std::string varName);

	bool areInUsesProcRelationship(std::string procName, std::string varName);

	//get modifies statement-variable
	std::unordered_map<int, std::set<std::string>> getStmtModifiesVarsMap();
	
	std::set<std::string> getModifiesVarsFromStmt(int stmtNum);

	std::set<int> getModifiesStmtsFromVar(std::string varName);

	bool areInModifiesStmtRelationship(int stmtNum, std::string varName);

	//get modifies procedure-variable
	std::set<std::string> getModifiesVarsFromProc(std::string procName);

	std::set<std::string> getModifiesProcsFromVar(std::string varName);

	bool areInModifiesProcRelationship(std::string procName, std::string varName);

	//get calls
	std::set<std::string> getCallsCallerNames(std::string calleeName);

	std::set<std::string> getCallsCalleeNames(std::string callerName);

	bool areInCallsRelationship(std::string callerName, std::string calleeName);

	bool isCallsEmpty();

	//get calls*
	std::set<std::string> getCallsStarCallerNames(std::string calleeName);

	std::set<std::string> getCallsStarCalleeNames(std::string callerName);

	bool areInCallsStarRelationship(std::string callerName, std::string calleeName);

	bool isCallsStarEmpty();

	//get next
	std::unordered_map<int, std::set<int>> getPreviousToNextStmtsMap();

	std::set<int> getPreviousStmtNums(int nextStmtNum);

	std::set<int> getNextStmtNums(int previousStmtNum);

	bool areInNextRelationship(int previousStmtNum, int nextStmtNum);

	bool isNextEmpty();

	//get next*
	void prepareNextStarTable();

	std::set<int> getStarPreviousStmtNums(int nextStmtNum);

	std::set<int> getStarNextStmtNums(int previousStmtNum);

	bool areInNextStarRelationship(int previousStmtNum, int nextStmtNum);

	bool isNextStarEmpty();

	void clearNextStar();

	//get affects
	std::set<int> getAffectsModifierStmtNums(int userStmtNum);

	std::set<int> getAffectsUserStmtNums(int modifierStmtNum);

	bool areInAffectsRelationship(int modifierStmtNum, int userStmtNum);

	bool isAffectsEmpty();

	void clearAffects();

	//get affects*
	std::set<int> getAffectsStarModifierStmtNums(int userStmtNum);

	std::set<int> getAffectsStarUserStmtNums(int modifierStmtNum);

	bool areInAffectsStarRelationship(int modifierStmtNum, int userStmtNum);

	bool isAffectsStarEmpty();

	void clearAffectsStar();

	//get with (read)
	std::string getWithReadVarName(int readLineNum, std::string invalidVarName);

	//get with (print)
	std::string getWithPrintVarName(int printLineNum, std::string invalidVarName);

	//get with (call)
	std::string getWithCallProcName(int callLineNum, std::string invalidProcName);

	//get assign pattern
	std::set<int> getAssignStmtsFromVar(std::string lhsVarName);

	std::vector<std::string> getAssignExprsFromStmt(int assignStmtNum);

	std::set<int> getAssignStmtsFromExpr(std::vector<std::string> rhsExpr);

	std::vector<std::string> getAssignExprsFromVar(std::string lhsVarName);

	//get while pattern
	std::set<int> getWhileStmtsWithVars();

	std::set<int> getWhileStmtsFromVar(std::string controlVarName);

	//get if pattern
	std::set<int> getIfStmtsWithVars();

	std::set<int> getIfStmtsFromVar(std::string controlVarName);

	//get cache
	std::unordered_map<std::pair<int, int>, bool, PairHasher<int, int>> getCache();

	//clear cache
	void clearCache();

private:
	EntityTable<std::string> procTable;
	EntityTable<std::string> varTable;
	EntityTable<std::string> constTable;
	EntityTable<Line> lineTable;
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
	SourceProcessor* sp;
	std::unordered_map<std::pair<int, int>, bool, PairHasher<int, int>> affectsCache;
};
