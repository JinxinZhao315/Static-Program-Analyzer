#include <unordered_map>
#include <string>
#include <unordered_set>
#include "Utility.h"

#pragma once 

class PQLRefConsistentLogic {
private:
    // TODO: Put these constants into Utility class
	std::string PROCEDURE = "procedure";
	std::string IDENT_STRING = "quotedIdent";
	std::string STMT = "stmt";
	std::string READ = "read";
	std::string PRINT = "print";
	std::string CALL = "call";
	std::string WHILE = "while";
	std::string IF = "if";
	std::string ASSIGN = "assign";
	std::string UNDERSCORE = "_";
	std::string INTEGER = "integer";
	std::string VARIABLE = "variable";
	std::string PROCNAME = "procName";
	std::string STMTNUM = "stmt#";
	std::string VALUE = "value";
	std::string CONSTANT = "constant";

	std::unordered_map<std::string,
		std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>> relationLogicMap;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> withLogicMap;
	std::unordered_set<std::string> procUsesModifiesSet;
	std::unordered_set<std::string> stmtSet;
	std::unordered_set<std::string> stmtModifiesSet;
	std::unordered_set<std::string> stmtUsesSet;
	std::unordered_set<std::string> varSet;
	std::unordered_set<std::string> procCallsSet;

	std::pair<std::string, std::string> procNameNamePair;
	std::pair<std::string, std::string> stmtNumIntPair;
	std::pair<std::string, std::string> valueIntPair;
	std::pair<std::string, std::string> varNameNamePair;

	std::unordered_map<std::string, std::string> procPairSet;
	std::unordered_map<std::string, std::string> callPairSet;
	std::unordered_map<std::string, std::string> constantPairSet;
	std::unordered_map<std::string, std::string> variablePairSet;
	std::unordered_map<std::string, std::string> stmtPairSet;
	std::unordered_map<std::string, std::string> printPairSet;
	std::unordered_map<std::string, std::string> readPairSet;
	std::unordered_map<std::string, std::string> assignPairSet;
	std::unordered_map<std::string, std::string> ifPairSet;
	std::unordered_map<std::string, std::string> whilePairSet;

	void createUsesModifiesProcRef();
	void createCallsProcRef();
	void createStmtRef();
	void createStmtRefModifies();
	void createStmtRefUses();
	void createVarRef();

	void createProcNameNamePair();
	void createStmtNumIntPair();
	void createValueIntPair();
	void createVarNameNamePair();
	void createProcPairSet();
	void createCallPairSet();
	void createConstantPairSet();
	void createVariablePairSet();
	void createStmtPairSet();
	void createPrintPairSet();
	void createReadPairSet();
	void createAssignPairSet();
	void createWhilePairSet();
	void createIfPairSet();

public:

	PQLRefConsistentLogic();

	~PQLRefConsistentLogic();

	bool hasRelationRef(std::string relation, std::string leftType, std::string rightType);

	bool hasWithRef(std::string leftAttrType, std::string leftAttrName, std::string rightValue);
};