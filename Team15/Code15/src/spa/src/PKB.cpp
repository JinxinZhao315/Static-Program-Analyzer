#include "PKB.h"

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
void PKB::addProc(std::string procName) {
	procTable.addEntity(procName);
}

//SP variable
void PKB::addVar(std::string varName) {
	varTable.addEntity(varName);
}

//SP constant
void PKB::addConst(std::string constVal) {
	constTable.addEntity(constVal);
}

//SP statement
void PKB::addStmt(Tokens::Keyword stmtType, int stmtNum) {
	stmtTable.addStatementNumber(stmtType, stmtNum);
}

//SP follows
void PKB::addFollows(int leaderNum, int followerNum) {
	followsTable.addOneToOneAbstraction(leaderNum, followerNum);
}

//SP follows*
void PKB::addFollowsStar(int leaderNum, std::set<int> followerNums) {
	followsStarTable.addOneToManyAbstraction(leaderNum, followerNums);
}

//SP parent
void PKB::addParent(int parentNum, int childNum) {
	parentTable.addOneToOneAbstraction(parentNum, childNum);
}

//SP parent*
void PKB::addParentStar(int parentNum, std::set<int> childrenNums) {
	parentStarTable.addOneToManyAbstraction(parentNum, childrenNums);
}

//SP uses statement-variable
void PKB::addUsesStmt(int stmtNum, std::set<std::string> varNames) {
	usesStmtTable.addOneToManyAbstraction(stmtNum, varNames);
}

//SP uses procedure-variable
void PKB::addUsesProc(std::string procName, std::set<std::string> varNames) {
	usesProcTable.addOneToManyAbstraction(procName, varNames);
}

//SP modifies statement-variable
void PKB::addModifiesStmt(int stmtNum, std::set<std::string> varNames) {
	modifiesStmtTable.addOneToManyAbstraction(stmtNum, varNames);
}

//SP modifies procedure-variable
void PKB::addModifiesProc(std::string procName, std::set<std::string> varNames) {
	modifiesProcTable.addOneToManyAbstraction(procName, varNames);
}

//SP pattern
void PKB::addPattern(int assignStmtNum, string lhsVarName, set<vector<string>> rhsPostfixes) {
	patternTable.addPattern(assignStmtNum, lhsVarName, rhsPostfixes);
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

std::set<int> PKB::getAllStmtNumsByType(Tokens::Keyword stmtType) {
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
	return (followsTable.isEmpty() || followsStarTable.isEmpty());
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

//QPS parent
int PKB::getParentParentNum(int childNum) {
	return parentTable.getOneLeft(childNum);
}

int PKB::getParentChildNum(int parentNum) {
	return parentTable.getOneRight(parentNum);
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
	return parentStarTable.getManyLeft(parent);
}

bool PKB::areInParentStarRelationship(int parentNum, int childNum) {
	return parentStarTable.inOneToManyRelationship(parentNum, childNum);
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
