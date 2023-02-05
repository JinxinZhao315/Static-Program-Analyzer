#include "PKB.h"

using namespace std;

void PKB::addProc(std::string procName) {
	return procTable.addEntity(procName);
}

void PKB::addStmt(int stmtNum, std::string stmtType) {
	if (stmtType == "read") {
		readTable.addStatementNumber(stmtNum);
	}
	else if (stmtType == "print") {
		printTable.addStatementNumber(stmtNum);
	}
	else if (stmtType == "assign") {
		assignTable.addStatementNumber(stmtNum);
	}
	else if (stmtType == "call") {
		callTable.addStatementNumber(stmtNum);
	}
	else if (stmtType == "while") {
		whileTable.addStatementNumber(stmtNum);
	}
	else if (stmtType == "if") {
		ifTable.addStatementNumber(stmtNum);
	}
	return stmtTable.addStatementNumber(stmtNum);
}

void PKB::addVar(std::string varName) {
	return varTable.addEntity(varName);
}

void PKB::addConst(std::string constVal) {
	return constTable.addEntity(constVal);
}

void PKB::addFollows(int leaderNum, int followerNum) {
	return followsTable.addFollows(leaderNum, followerNum);
}

void PKB::addFollowsStar(int leaderNum, std::set<int> followerNums) {
	return followsStarTable.addFollowsStar(leaderNum, followerNums);
}

std::set<std::string> PKB::getAllProcNames() {
	return procTable.getAllEntities();
}

std::set<int> PKB::getAllStmtNums() {
	return stmtTable.getAllStatementNumbers();
}

std::set<int> PKB::getAllStmtNumsByType(std::string stmtType) {
	if (stmtType == "read") {
		return readTable.getAllStatementNumbers();
	}
	else if (stmtType == "print") {
		return printTable.getAllStatementNumbers();
	}
	else if (stmtType == "assign") {
		return assignTable.getAllStatementNumbers();
	}
	else if (stmtType == "call") {
		return callTable.getAllStatementNumbers();
	}
	else if (stmtType == "while") {
		return whileTable.getAllStatementNumbers();
	}
	else {
		return ifTable.getAllStatementNumbers();
	}
}

std::set<std::string> PKB::getAllVarNames() {
	return varTable.getAllEntities();
}

std::set<std::string> PKB::getAllConstVals() {
	return constTable.getAllEntities();
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