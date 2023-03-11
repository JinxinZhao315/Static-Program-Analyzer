#include "pkb/include/PKB.h"

PKB::PKB() {
	procTable = EntityTable<std::string>();
	varTable = EntityTable<std::string>();
	constTable = EntityTable<std::string>();
	stmtTable = StatementTable();
	followsTable = RelationshipTable<int, int>();
	followsStarTable = RelationshipTable<int, int>();
	parentTable = RelationshipTable<int, int>();
	parentStarTable = RelationshipTable<int, int>();
	usesStmtTable = RelationshipTable<int, std::string>();
	usesProcTable = RelationshipTable<std::string, std::string>();
	assignPatternTable = PatternTable();
	whilePatternTable = PatternTable();
	ifPatternTable = PatternTable();
	callsTable = RelationshipTable<std::string, std::string>();
	callsStarTable = RelationshipTable<std::string, std::string>();
	nextTable = RelationshipTable<int, int>();
	nextStarTable = RelationshipTable<int, int>();
	affectsTable = RelationshipTable<int, int>();
	affectsStarTable = RelationshipTable<int, int>();
}

//SP procedure
void PKB::addAllProcs(std::set<std::string> procNames) {
	procTable.addAllEntities(procNames);
}

//SP variable
void PKB::addAllVars(std::set<std::string> varNames) {
	varTable.addAllEntities(varNames);
}

//SP constant
void PKB::addAllConsts(std::set<std::string> constVals) {
	constTable.addAllEntities(constVals);
}

//SP statement
void PKB::addAllStmts(std::unordered_map<std::string, std::set<int>> stmtNums) {
	stmtTable.addAllStatementsByType(stmtNums);
	stmtTable.addAllStatementsRegardlessOfType(stmtNums);
}

//SP follows
void PKB::addAllFollows(std::unordered_map<int, int> allLeaderToFollower) {
	followsTable.addAllOneToOneRelationships(allLeaderToFollower);
}

//SP follows*
void PKB::addAllFollowsStar(std::unordered_map<int, std::set<int>> allLeaderToFollowers) {
	followsStarTable.addAllOneToManyRelationships(allLeaderToFollowers);
}

//SP parent
void PKB::addAllParent(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentTable.addAllOneSidedOnetoManyRelationships(allParentToChildren);
}

//SP parent*
void PKB::addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentStarTable.addAllOneToManyRelationships(allParentToChildren);
}

//SP uses statement-variable
void PKB::addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	usesStmtTable.addAllOneToManyRelationships(allStmtToVars);
}

//SP uses procedure-variable
void PKB::addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	usesProcTable.addAllOneToManyRelationships(allProcToVars);
}

//SP modifies statement-variable
void PKB::addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	modifiesStmtTable.addAllOneToManyRelationships(allStmtToVars);
}

//SP modifies procedure-variable
void PKB::addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	modifiesProcTable.addAllOneToManyRelationships(allProcToVars);
}

//SP assign pattern
void PKB::addAllAssignPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
	assignPatternTable.addAllAssignPatterns(lhsVarToRhsLine);
}

//SP while pattern
void PKB::addAllWhilePatterns(std::unordered_map<std::string, std::set<Line>> controlVarToWhileLine) {
	whilePatternTable.addAllWhileOrIfPatterns(controlVarToWhileLine);
}

//SP if pattern
void PKB::addAllIfPatterns(std::unordered_map<std::string, std::set<Line>> controlVarToIfLine) {
	ifPatternTable.addAllWhileOrIfPatterns(controlVarToIfLine);
}

//SP calls
void PKB::addAllCalls(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees) {
	callsTable.addAllOneToManyRelationships(allCallertoCallees);
}

//SP calls*
void PKB::addAllCallsStar(std::unordered_map<std::string, std::set<std::string>> allCallertoCallees) {
	callsStarTable.addAllOneToManyRelationships(allCallertoCallees);
}

//SP next
void PKB::addAllNext(std::unordered_map<int, std::set<int>> allPreviousToNexts) {
	nextTable.addAllOneSidedOnetoManyRelationships(allPreviousToNexts);
}

//SP next*
void PKB::addAllNextStar(std::unordered_map<int, std::set<int>> allPreviousToNexts) {
	nextStarTable.addAllOneToManyRelationships(allPreviousToNexts);
	nextStarTable.setToReady();
}

//SP affects
void PKB::addAllAffects(std::unordered_map<int, std::set<int>> allModifierToUsers) {
	affectsTable.addAllOneToManyRelationships(allModifierToUsers);
	affectsTable.setToReady();
}

//SP affects*
void PKB::addAllAffectsStar(std::unordered_map<int, std::set<int>> allModifierToUsers) {
	affectsStarTable.addAllOneToManyRelationships(allModifierToUsers);
	affectsStarTable.setToReady();
}

//SP with read
void PKB::addAllWithRead(unordered_map<int, std::string> readLineNumToVarName) {
	withReadTable.addAllOneToOneRelationships(readLineNumToVarName);
}

//SP with print
void PKB::addAllWithPrint(unordered_map<int, std::string> printLineNumToVarName) {
	withPrintTable.addAllOneToOneRelationships(printLineNumToVarName);
}

//SP with call
void PKB::addAllWithCall(unordered_map<int, std::string> callLineNumToProcName) {
	withCallTable.addAllOneToOneRelationships(callLineNumToProcName);
}

//QPS procedure
std::set<std::string> PKB::getAllProcNames() {
	return procTable.getAllEntities();
}

//QPS variable
std::set<std::string> PKB::getAllVarNames() {
	return varTable.getAllEntities();
}

//QPS constant
std::set<std::string> PKB::getAllConstVals() {
	return constTable.getAllEntities();
}

//QPS statement
std::set<int> PKB::getAllStmtNums() {
	return stmtTable.getAllStatementNumbers();
}

std::set<int> PKB::getAllStmtNumsByType(std::string stmtType) {
	return stmtTable.getAllStatementNumbersByType(stmtType);
}

//QPS follow
int PKB::getFollowsLeaderNum(int followerNum, int invalidLeaderNum) {
	return followsTable.getOneLeft(followerNum, invalidLeaderNum);
}

int PKB::getFollowsFollowerNum(int leaderNum, int invalidFollowerNum) {
	return followsTable.getOneRight(leaderNum, invalidFollowerNum);
}

bool PKB::areInFollowsRelationship(int leaderNum, int followerNum) {
	return followsTable.inOneToOneRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsEmpty() {
	return followsTable.isEmpty();
}

//QPS follows*
std::set<int> PKB::getFollowsStarLeaderNums(int followerNum) {
	return followsStarTable.getManyLeft(followerNum);
}

std::set<int> PKB::getFollowsStarFollowerNums(int leaderNum) {
	return followsStarTable.getManyRight(leaderNum);
}

bool PKB::areInFollowsStarRelationship(int leaderNum, int followerNum) {
	return followsStarTable.inOneToManyRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsStarEmpty() {
	return followsStarTable.isEmpty();
}

//QPS parent
int PKB::getParentParentNum(int childNum, int invalidParentNum) {
	return parentTable.getOneLeft(childNum, invalidParentNum);
}

std::set<int> PKB::getParentChildNums(int parentNum) {
	return parentTable.getManyRight(parentNum);
}

bool PKB::areInParentRelationship(int parentNum, int childNum) {
	return parentTable.inOneToOneRelationship(parentNum, childNum);
}

bool PKB::isParentEmpty() {
	return parentTable.isEmpty();
}

//QPS parent*
std::set<int> PKB::getParentStarParentNums(int childNum) {
	return parentStarTable.getManyLeft(childNum);
}

std::set<int> PKB::getParentStarChildNums(int parentNum) {
	return parentStarTable.getManyRight(parentNum);
}

bool PKB::areInParentStarRelationship(int parentNum, int childNum) {
	return parentStarTable.inOneToManyRelationship(parentNum, childNum);
}

bool PKB::isParentStarEmpty() {
	return parentStarTable.isEmpty();
}

//QPS uses statement-variable
std::set<std::string> PKB::getUsesVarsFromStmt(int stmtNum) {
	return usesStmtTable.getManyRight(stmtNum);
}

std::set<int> PKB::getUsesStmtsFromVar(std::string varName) {
	return usesStmtTable.getManyLeft(varName);
}

bool PKB::areInUsesStmtRelationship(int stmtNum, std::string varName) {
	return usesStmtTable.inOneToManyRelationship(stmtNum, varName);
}

//QPS uses procedure-variable
std::set<std::string> PKB::getUsesVarsFromProc(std::string procName) {
	return usesProcTable.getManyRight(procName);
}

std::set<std::string> PKB::getUsesProcsFromVar(std::string varName) {
	return usesProcTable.getManyLeft(varName);
}

bool PKB::areInUsesProcRelationship(std::string procName, std::string varName) {
	return usesProcTable.inOneToManyRelationship(procName, varName);
}

//QPS modifies statement-variable
std::set<std::string> PKB::getModifiesVarsFromStmt(int stmtNum) {
	return modifiesStmtTable.getManyRight(stmtNum);
}

std::set<int> PKB::getModifiesStmtsFromVar(std::string varName) {
	return modifiesStmtTable.getManyLeft(varName);
}

bool PKB::areInModifiesStmtRelationship(int stmtNum, std::string varName) {
	return modifiesStmtTable.inOneToManyRelationship(stmtNum, varName);
}

//QPS modifies procedure-variable
std::set<std::string> PKB::getModifiesVarsFromProc(std::string procName) {
	return modifiesProcTable.getManyRight(procName);
}

std::set<std::string> PKB::getModifiesProcsFromVar(std::string varName) {
	return modifiesProcTable.getManyLeft(varName);
}

bool PKB::areInModifiesProcRelationship(std::string procName, std::string varName) {
	return modifiesProcTable.inOneToManyRelationship(procName, varName);
}

//QPS assign pattern
std::string PKB::getAssignVarFromStmt(int assignStmtNum) {
	return assignPatternTable.getVarFromStmt(assignStmtNum);
}

std::set<int> PKB::getAssignStmtsFromVar(std::string lhsVarName) {
	return assignPatternTable.getStmtsFromVar(lhsVarName);
}

std::set<std::vector<std::string>> PKB::getAssignExprsFromStmt(int assignStmtNum) {
	return assignPatternTable.getExprsFromStmt(assignStmtNum);
}

std::set<int> PKB::getAssignStmtsFromExpr(std::vector<std::string> rhsExpr) {
	return assignPatternTable.getStmtsFromExpr(rhsExpr);
}

std::set<std::vector<std::string>> PKB::getAssignExprsFromVar(std::string lhsVarName) {
	return assignPatternTable.getExprsFromVar(lhsVarName);
}

std::set<std::string> PKB::getAssignVarsFromExpr(std::vector<std::string> rhsExpr) {
	return assignPatternTable.getVarsFromExpr(rhsExpr);
}

//QPS while pattern
std::set<int> PKB::getWhileStmtsWithVars() {
	return whilePatternTable.getAllStmts();
}

std::set<int> PKB::getWhileStmtsFromVar(std::string controlVarName) {
	return whilePatternTable.getStmtsFromVar(controlVarName);
}

std::set<std::string> PKB::getWhileVarsFromStmt(int whileStmtNum) {
	return whilePatternTable.getVarsFromStmt(whileStmtNum);
}

//QPS if pattern
std::set<int> PKB::getIfStmtsWithVars() {
	return ifPatternTable.getAllStmts();
}

std::set<int> PKB::getIfStmtsFromVar(std::string controlVarName) {
	return ifPatternTable.getStmtsFromVar(controlVarName);
}

std::set<std::string> PKB::getIfVarsFromStmt(int ifStmtNum) {
	return ifPatternTable.getVarsFromStmt(ifStmtNum);
}

//QPS calls
std::set<std::string> PKB::getCallsCallerNames(std::string calleeName) {
	return callsTable.getManyLeft(calleeName);
}

std::set<std::string> PKB::getCallsCalleeNames(std::string callerName) {
	return callsTable.getManyRight(callerName);
}

bool PKB::areInCallsRelationship(std::string callerName, std::string calleeName) {
	return callsTable.inOneToManyRelationship(callerName, calleeName);
}

bool PKB::isCallsEmpty() {
	return callsTable.isEmpty();
}

//QPS calls*
std::set<std::string> PKB::getCallsStarCallerNames(std::string calleeName) {
	return callsStarTable.getManyLeft(calleeName);
}

std::set<std::string> PKB::getCallsStarCalleeNames(std::string callerName) {
	return callsStarTable.getManyRight(callerName);
}

bool PKB::areInCallsStarRelationship(std::string callerName, std::string calleeName) {
	return callsStarTable.inOneToManyRelationship(callerName, calleeName);
}

bool PKB::isCallsStarEmpty() {
	return callsStarTable.isEmpty();
}

//QPS next
int PKB::getPreviousStmtNum(int nextStmtNum, int invalidPreviousStmtNum) {
	return nextTable.getOneLeft(nextStmtNum, invalidPreviousStmtNum);
}

std::set<int> PKB::getNextStmtNums(int previousStmtNum) {
	return nextTable.getManyRight(previousStmtNum);
}

bool PKB::areInNextRelationship(int previousStmtNum, int nextStmtNum) {
	return nextTable.inOneToOneRelationship(previousStmtNum, nextStmtNum);
}

bool PKB::isNextEmpty() {
	return nextTable.isEmpty();
}

//QPS next*
std::set<int> PKB::getStarPreviousStmtNums(int nextStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.getManyLeft(nextStmtNum);
	}
	return nextStarTable.getManyLeft(nextStmtNum);//TODO
}

std::set<int> PKB::getStarNextStmtNums(int previousStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.getManyRight(previousStmtNum);
	}
	return nextStarTable.getManyRight(previousStmtNum);//TODO
}

bool PKB::areInNextStarRelationship(int previousStmtNum, int nextStmtNum) {
	if (nextStarTable.checkReadiness()) {
		return nextStarTable.inOneToManyRelationship(previousStmtNum, nextStmtNum);
	}
	return nextStarTable.inOneToManyRelationship(previousStmtNum, nextStmtNum);//TODO
}

bool PKB::isNextStarEmpty() {
	return nextStarTable.isEmpty();
}

void PKB::clearNextStar() {
	nextStarTable.clearMaps();
	nextStarTable.setToUnready();
}

//QPS affects
std::set<int> PKB::getAffectsModifierStmtNums(int userStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.getManyLeft(userStmtNum);
	}
	return affectsTable.getManyLeft(userStmtNum);//TODO
}

std::set<int> PKB::getAffectsUserStmtNums(int modifierStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.getManyRight(modifierStmtNum);
	}
	return affectsTable.getManyRight(modifierStmtNum);//TODO
}

bool PKB::areInAffectsRelationship(int modifierStmtNum, int userStmtNum) {
	if (affectsTable.checkReadiness()) {
		return affectsTable.inOneToManyRelationship(modifierStmtNum, userStmtNum);
	}
	return affectsTable.inOneToManyRelationship(modifierStmtNum, userStmtNum);//TODO
}

bool PKB::isAffectsEmpty() {
	return affectsTable.isEmpty();
}

void PKB::clearAffects() {
	affectsTable.clearMaps();
	affectsTable.setToUnready();
}

//QPS affects*
std::set<int> PKB::getAffectsStarModifierStmtNums(int userStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.getManyLeft(userStmtNum);
	}
	return affectsStarTable.getManyLeft(userStmtNum);//TODO
}

std::set<int> PKB::getAffectsStarUserStmtNums(int modifierStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.getManyRight(modifierStmtNum);
	}
	return affectsStarTable.getManyRight(modifierStmtNum);//TODO
}

bool PKB::areInAffectsStarRelationship(int modifierStmtNum, int userStmtNum) {
	if (affectsStarTable.checkReadiness()) {
		return affectsStarTable.inOneToManyRelationship(modifierStmtNum, userStmtNum);
	}
	return affectsStarTable.inOneToManyRelationship(modifierStmtNum, userStmtNum);//TODO
}

bool PKB::isAffectsStarEmpty() {
	return affectsStarTable.isEmpty();
}

void PKB::clearAffectsStar() {
	affectsStarTable.clearMaps();
	affectsStarTable.setToUnready();
}

//QPS with read
std::string PKB::getWithReadVarName(int readLineNum, std::string invalidVarName) {
	return withReadTable.getOneRight(readLineNum, invalidVarName);
}

//QPS with print
std::string PKB::getWithPrintVarName(int printLineNum, std::string invalidVarName) {
	return withPrintTable.getOneRight(printLineNum, invalidVarName);
}

//QPS with call
std::string PKB::getWithCallProcName(int callLineNum, std::string invalidProcName) {
	return withCallTable.getOneRight(callLineNum, invalidProcName);
}
