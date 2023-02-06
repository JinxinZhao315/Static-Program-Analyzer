#include "PKB.h"

using namespace std;

PKB::PKB() {
	procTable = ProcedureTable::ProcedureTable();
	stmtTable = StatementTable::StatementTable();
	varTable = VariableTable::VariableTable();
	constTable = ConstantTable::ConstantTable();
	followsTable = FollowsTable::FollowsTable();
	followsStarTable = FollowsStarTable::FollowsStarTable();
}

void PKB::addProc(std::string procName) {
	procTable.addProcedureName(procName);
}

void PKB::addStmt(Tokens::Keyword stmtType, int stmtNum) {
	stmtTable.addStatementNumber(stmtNum);
	stmtTable.addStatementNumberByType(stmtNum, stmtType);
}

void PKB::addVar(std::string varName) {
	varTable.addVariableName(varName);
}

void PKB::addConst(std::string constVal) {
	constTable.addConstantValue(constVal);
}

void PKB::addFollows(int leaderNum, int followerNum) {
	followsTable.addFollows(leaderNum, followerNum);
}

void PKB::addFollowsStar(int leaderNum, std::set<int> followerNums) {
	followsStarTable.addFollowsStar(leaderNum, followerNums);
}

std::set<std::string> PKB::getAllProcNames() {
	return procTable.getAllProcedureNames();
}

std::set<int> PKB::getAllStmtNums() {
	return stmtTable.getAllStatementNumbers();
}

std::set<int> PKB::getAllStmtNumsByType(Tokens::Keyword stmtType) {
	return stmtTable.getAllStatementNumbersByType(stmtType);
}

std::set<std::string> PKB::getAllVarNames() {
	return varTable.getAllVariableNames();
}

std::set<std::string> PKB::getAllConstVals() {
	return constTable.getAllConstantValues();
}

int PKB::getFollowsLeaderNum(int followerNum) {
	return followsTable.getLeader(followerNum);
}

int PKB::getFollowsFollowerNum(int leaderNum) {
	return followsTable.getFollower(leaderNum);
}

std::set<int> PKB::getFollowsStarLeaderNums(int followerNum) {
	return followsStarTable.getLeaders(followerNum);
}

std::set<int> PKB::getFollowsStarFollowerNums(int leaderNum) {
	return followsStarTable.getFollowers(leaderNum);
}

bool PKB::areInFollowsRelationship(int leaderNum, int followerNum) {
	return followsTable.inRelationship(leaderNum, followerNum);
}

bool PKB::areInFollowsStarRelationship(int leaderNum, int followerNum) {
	return followsStarTable.inRelationship(leaderNum, followerNum);
}

bool PKB::isFollowsEmpty() {
	return followsTable.isEmpty();
}
