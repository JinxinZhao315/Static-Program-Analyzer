#include "QPS/include/tokenizer/PQLRefConsistentLogic.h"

void PQLRefConsistentLogic::createUsesModifiesProcRef() {
	procUsesModifiesSet.emplace(PROCEDURE);
	procUsesModifiesSet.emplace(INDENT_STRING);
}

void PQLRefConsistentLogic::createCallsProcRef() {
	procCallsSet.emplace(PROCEDURE);
	procCallsSet.emplace(INDENT_STRING);
	procCallsSet.emplace(UNDERSCORE);
}

void PQLRefConsistentLogic::createStmtRef() {
	stmtSet.emplace(STMT);
	stmtSet.emplace(ASSIGN);
	stmtSet.emplace(READ);
	stmtSet.emplace(PRINT);
	stmtSet.emplace(CALL);
	stmtSet.emplace(UNDERSCORE);
	stmtSet.emplace(INTEGER);
	stmtSet.emplace(WHILE);
	stmtSet.emplace(IF);
}

void PQLRefConsistentLogic::createStmtRefModifies() {
	stmtModifiesSet.emplace(STMT);
	stmtModifiesSet.emplace(ASSIGN);
	stmtModifiesSet.emplace(READ);
	stmtModifiesSet.emplace(CALL);
	stmtModifiesSet.emplace(INTEGER);
	stmtModifiesSet.emplace(WHILE);
	stmtModifiesSet.emplace(IF);
}

void PQLRefConsistentLogic::createStmtRefUses() {
	stmtUsesSet.emplace(STMT);
	stmtUsesSet.emplace(ASSIGN);
	stmtUsesSet.emplace(PRINT);
	stmtUsesSet.emplace(CALL);
	stmtUsesSet.emplace(INTEGER);
	stmtUsesSet.emplace(WHILE);
	stmtUsesSet.emplace(IF);
}

void PQLRefConsistentLogic::createVarRef() {
	varSet.emplace(VARIABLE);
	varSet.emplace(UNDERSCORE);
	varSet.emplace(INDENT_STRING);
}

PQLRefConsistentLogic::PQLRefConsistentLogic() {
	createUsesModifiesProcRef();
	createCallsProcRef();
	createStmtRef();
	createStmtRefModifies();
	createStmtRefUses();
	createVarRef();
	relationLogicMap.emplace("ModifiesP", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procUsesModifiesSet, varSet));
	relationLogicMap.emplace("ModifiesS", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtModifiesSet, varSet));
	relationLogicMap.emplace("UsesP", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procUsesModifiesSet, varSet));
	relationLogicMap.emplace("UsesS", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtUsesSet, varSet));
	relationLogicMap.emplace("Follows", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	relationLogicMap.emplace("Follows*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	relationLogicMap.emplace("Parent", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	relationLogicMap.emplace("Parent*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	relationLogicMap.emplace("Calls", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procCallsSet, procCallsSet));
	relationLogicMap.emplace("Calls*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procCallsSet, procCallsSet));
	relationLogicMap.emplace("Next", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	relationLogicMap.emplace("Next*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
}

bool PQLRefConsistentLogic::hasRelationRef(std::string relation, std::string leftType, std::string rightType) {
	std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>>::iterator setPairPointer = relationLogicMap.find(relation);
	std::unordered_set<std::string> leftSet = setPairPointer->second.first;
	std::unordered_set<std::string> rightSet = setPairPointer->second.second;
	bool inLeftSet = leftSet.find(leftType) != leftSet.end();
	bool inRightSet = rightSet.find(rightType) != rightSet.end();
	if (inLeftSet && inRightSet) {
		return true;
	}
	return false;
}

bool PQLRefConsistentLogic::hasWithRef(std::string relation, std::string leftType, std::string rightType) {
	std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>>::iterator setPairPointer = relationLogicMap.find(relation);
	std::unordered_set<std::string> leftSet = setPairPointer->second.first;
	std::unordered_set<std::string> rightSet = setPairPointer->second.second;
	bool inLeftSet = leftSet.find(leftType) != leftSet.end();
	bool inRightSet = rightSet.find(rightType) != rightSet.end();
	if (inLeftSet && inRightSet) {
		return true;
	}
	return false;
}

PQLRefConsistentLogic::~PQLRefConsistentLogic() {}


