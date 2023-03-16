#include "QPS/include/tokenizer/PQLRefConsistentLogic.h"

void PQLRefConsistentLogic::createUsesModifiesProcRef() {
	procUsesModifiesSet.emplace(PROCEDURE);
	procUsesModifiesSet.emplace(IDENT_STRING);
}

void PQLRefConsistentLogic::createCallsProcRef() {
	procCallsSet.emplace(PROCEDURE);
	procCallsSet.emplace(IDENT_STRING);
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
	varSet.emplace(IDENT_STRING);
}

void PQLRefConsistentLogic::createProcPairSet() {
	procPairSet.emplace(procNameNamePair);
}

void PQLRefConsistentLogic::createCallPairSet() {
	callPairSet.emplace(stmtNumIntPair);
	callPairSet.emplace(procNameNamePair);
}

void PQLRefConsistentLogic::createConstantPairSet() {
	constantPairSet.emplace(valueIntPair);
}

void PQLRefConsistentLogic::createVariablePairSet() {
	variablePairSet.emplace(varNameNamePair);
}

void PQLRefConsistentLogic::createStmtPairSet() {
	stmtPairSet.emplace(stmtNumIntPair);
}

void PQLRefConsistentLogic::createPrintPairSet() {
	printPairSet.emplace(stmtNumIntPair);
	printPairSet.emplace(varNameNamePair);
}

void PQLRefConsistentLogic::createReadPairSet() {
	readPairSet.emplace(stmtNumIntPair);
	readPairSet.emplace(varNameNamePair);
}

void PQLRefConsistentLogic::createAssignPairSet() {
	assignPairSet.emplace(stmtNumIntPair);
}

void PQLRefConsistentLogic::createWhilePairSet() {
	whilePairSet.emplace(stmtNumIntPair);
}

void PQLRefConsistentLogic::createIfPairSet() {
	ifPairSet.emplace(stmtNumIntPair);
}

void PQLRefConsistentLogic::createProcNameNamePair() {
	this->procNameNamePair = std::make_pair(PROCNAME, IDENT_STRING);
}
void PQLRefConsistentLogic::createStmtNumIntPair() {
	this->stmtNumIntPair = std::make_pair(STMTNUM, INTEGER);
}
void PQLRefConsistentLogic::createValueIntPair() {
	this->valueIntPair = std::make_pair(VALUE, INTEGER);
}
void PQLRefConsistentLogic::createVarNameNamePair() {
	this->varNameNamePair = std::make_pair(VARNAME, IDENT_STRING);
}


PQLRefConsistentLogic::PQLRefConsistentLogic() {
	createUsesModifiesProcRef();
	createCallsProcRef();
	createStmtRef();
	createStmtRefModifies();
	createStmtRefUses();
	createVarRef();

	createProcNameNamePair();
	createStmtNumIntPair();
	createValueIntPair();
	createVarNameNamePair();
	createAssignPairSet();
	createCallPairSet();
	createPrintPairSet();
	createReadPairSet();
	createIfPairSet();
	createWhilePairSet();
	createProcPairSet();
	createVariablePairSet();
	createConstantPairSet();
	createStmtPairSet();

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

	withLogicMap.emplace(PROCEDURE, procPairSet);
	withLogicMap.emplace(CALL, callPairSet);
	withLogicMap.emplace(VARIABLE, variablePairSet);
	withLogicMap.emplace(READ, readPairSet);
	withLogicMap.emplace(WHILE, whilePairSet);
	withLogicMap.emplace(IF, ifPairSet);
	withLogicMap.emplace(ASSIGN, assignPairSet);
	withLogicMap.emplace(STMT, stmtPairSet);
	withLogicMap.emplace(PRINT, printPairSet);
	withLogicMap.emplace(CONSTANT, constantPairSet);
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

bool PQLRefConsistentLogic::isWithRefCompatible(std::string leftAttrType, std::string leftAttrName, std::string rightValue) {
	bool isLeftAttrTypeValid = withLogicMap.find(leftAttrType) != withLogicMap.end();
	if (!isLeftAttrTypeValid) {
		return false;
	}
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>::iterator pairSetPointer = withLogicMap.find(leftAttrType);
	std::unordered_map<std::string, std::string> pairSet = pairSetPointer->second;


	bool isLeftAttrNameValid = pairSet.find(leftAttrName) != pairSet.end();
	if (!isLeftAttrNameValid) {
		return false;
	}
	std::string desiredRightValueType = pairSet.find(leftAttrName)->second;
	std::string actualRightValueType = Utility::getReferenceType(rightValue);
	return desiredRightValueType == actualRightValueType;
}

bool PQLRefConsistentLogic::isWithRefCompatible(std::string leftAttrType, std::string leftAttrName, std::string rightAttrType, std::string rightAttrName) {
	bool isLeftAttrTypeValid = withLogicMap.find(leftAttrType) != withLogicMap.end();
	if (!isLeftAttrTypeValid) {
		return false;
	}
	bool isRightAttrTypeValid = withLogicMap.find(rightAttrType) != withLogicMap.end();
	if (!isRightAttrTypeValid) {
		return false;
	}

	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>::iterator leftPairSetPointer = withLogicMap.find(leftAttrType);
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>::iterator rightPairSetPointer = withLogicMap.find(rightAttrType);
	std::unordered_map<std::string, std::string> leftPairSet = leftPairSetPointer->second;
	std::unordered_map<std::string, std::string> rightPairSet = rightPairSetPointer->second;

	bool isLeftAttrNameValid = leftPairSet.find(leftAttrName) != leftPairSet.end();
	if (!isLeftAttrNameValid) {
		return false;
	}
	bool isRightAttrNameValid = rightPairSet.find(rightAttrName) != rightPairSet.end();
	if (!isRightAttrNameValid) {
		return false;
	}
	std::string actualRightValueType = rightPairSet.find(rightAttrName)->second;
	std::string actualLeftValueType = leftPairSet.find(leftAttrName)->second;
	return actualRightValueType == actualLeftValueType;
}

PQLRefConsistentLogic::~PQLRefConsistentLogic() {}
