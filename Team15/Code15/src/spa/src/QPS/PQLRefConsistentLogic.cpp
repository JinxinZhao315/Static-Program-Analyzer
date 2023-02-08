#include "PQLRefConsistentLogic.h"

void PQLRefConsistentLogic::createProcRef() {
	procSet.emplace(PROCEDURE);
	procSet.emplace(INDENT_STRING);
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
	createProcRef();
	createStmtRef();
	createStmtRefModifies();
	createStmtRefUses();
	createVarRef();
	logicMap.emplace("ModifiesP", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procSet, varSet));
	logicMap.emplace("ModifiesS", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtModifiesSet, varSet));
	logicMap.emplace("UsesP", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(procSet, varSet));
	logicMap.emplace("UsesS", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtUsesSet, varSet));
	logicMap.emplace("Follows", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	logicMap.emplace("Follows*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	logicMap.emplace("Parent", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
	logicMap.emplace("Parent*", std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>(stmtSet, stmtSet));
}

bool PQLRefConsistentLogic::hasRef(std::string relation, std::string leftType, std::string rightType) {
	std::unordered_map<std::string, std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>>::iterator setPairPointer = logicMap.find(relation);
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


