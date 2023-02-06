#include "PKBStub.h"

PKBStub::PKBStub(std::set<std::string> constSet, std::set<std::string> varNameSet,
	std::set<int> stmtNumberByType, std::set<int> stmtNums) : PKB() {}

std::set<std::string> PKBStub::getAllConstVals() {
	return this->constSet;
}
std::set<std::string> PKBStub::getAllVarNames() {
	return this->varNameSet;
}
std::set<int> PKBStub::getAllStmtNumsByType(std::string type) {
	return this->stmtNumberByType;
}
std::set<int> PKBStub::getAllStmtNums() {
	return this->stmtNums;
}