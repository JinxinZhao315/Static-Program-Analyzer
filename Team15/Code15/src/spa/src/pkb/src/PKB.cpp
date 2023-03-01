#include "pkb/include/PKB.h"

PKB::PKB() {
	procTable = EntityTable<std::string>();
	varTable = EntityTable<std::string>();
	constTable = EntityTable<std::string>();
	stmtTable = StatementTable();
	followsTable = AbstractionTable<int, int>();
	followsStarTable = AbstractionTable<int, int>();
	parentTable = AbstractionTable<int, int>();
	parentStarTable = AbstractionTable<int, int>();
	usesStmtTable = AbstractionTable<int, std::string>();
	usesProcTable = AbstractionTable<std::string, std::string>();
	patternTable = PatternTable();
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
void PKB::addAllStmts(std::unordered_map<string, std::set<int>> stmtNums) {
	stmtTable.addAllStatementsByType(stmtNums);
	stmtTable.addAllStatementsRegardlessOfType(stmtNums);
}

//SP follows
void PKB::addAllFollows(std::unordered_map<int, int> allLeaderToFollower) {
	followsTable.addAllOneToOneAbstractions(allLeaderToFollower);
}

//SP follows*
void PKB::addAllFollowsStar(std::unordered_map<int, std::set<int>> allLeaderToFollowers) {
	followsStarTable.addAllOneToManyAbstractions(allLeaderToFollowers);
}

//SP parent
void PKB::addAllParent(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentTable.addAllOneSidedOnetoManyAbstractions(allParentToChildren);
}

//SP parent*
void PKB::addAllParentStar(std::unordered_map<int, std::set<int>> allParentToChildren) {
	parentStarTable.addAllOneToManyAbstractions(allParentToChildren);
}

//SP uses statement-variable
void PKB::addAllUsesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	usesStmtTable.addAllOneToManyAbstractions(allStmtToVars);
}

//SP uses procedure-variable
void PKB::addAllUsesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	usesProcTable.addAllOneToManyAbstractions(allProcToVars);
}

//SP modifies statement-variable
void PKB::addAllModifiesStmt(std::unordered_map<int, std::set<std::string>> allStmtToVars) {
	modifiesStmtTable.addAllOneToManyAbstractions(allStmtToVars);
}

//SP modifies procedure-variable
void PKB::addAllModifiesProc(std::unordered_map<std::string, std::set<std::string>> allProcToVars) {
	modifiesProcTable.addAllOneToManyAbstractions(allProcToVars);
}

//SP pattern
void PKB::addAllPatterns(std::unordered_map<std::string, std::set<Line>> lhsVarToRhsLine) {
	patternTable.addAllPatterns(lhsVarToRhsLine);
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

std::set<int> PKB::getAllStmtNumsByType(string stmtType) { // TODO: @Galen please review
	return stmtTable.getAllStatementNumbersByType(stmtType);
}

//QPS follow
int PKB::getFollowsLeaderNum(int followerNum) {
	return followsTable.getOneLeft(followerNum);
}

int PKB::getFollowsFollowerNum(int leaderNum) {
	return followsTable.getOneRight(leaderNum);
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
int PKB::getParentParentNum(int childNum) {
	return parentTable.getOneLeft(childNum);
}

std::set<int> PKB::getParentChildrenNum(int parentNum) {
	return parentTable.getManyRight(parentNum);
}

bool PKB::areInParentRelationship(int parentNum, int childNum) {
	return parentTable.inOneToOneRelationship(parentNum, childNum);
}

bool PKB::isParentEmpty() {
	return parentTable.isEmpty();
}

//QPS parent*
std::set<int> PKB::getParentStarParentNums(int child) {
	return parentStarTable.getManyLeft(child);
}

std::set<int> PKB::getParentStarChildNums(int parent) {
	return parentStarTable.getManyRight(parent);
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

//QPS pattern
string PKB::getPatternVarFromStmt(int assignStmtNum) {
	return patternTable.getVarFromStmt(assignStmtNum);
}

set<int> PKB::getPatternStmtsFromVar(string lhsVarName) {
	return patternTable.getStmtsFromVar(lhsVarName);
}

set<vector<string>> PKB::getPatternPostfixesFromStmt(int assignStmtNum) {
	return patternTable.getPostfixesFromStmt(assignStmtNum);
}

set<int> PKB::getPatternStmtsFromPostfix(vector<string> rhsPostfix) {
	return patternTable.getStmtsFromPostfix(rhsPostfix);
}

set<vector<string>> PKB::getPatternPostfixesFromVar(string lhsVarName) {
	return patternTable.getPostfixesFromVar(lhsVarName);
}

set<string> PKB::getPatternVarsFromPostfix(vector<string> rhsPostfix) {
	return patternTable.getVarsFromPostfix(rhsPostfix);
}
