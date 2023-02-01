#include <unordered_map>
#include <string>
#include <unordered_set>

#pragma once 

class PQLRefConsistentLogic {
private:
	std::string PROCEDURE = "procedure";
	std::string INDENT_STRING = "indent_string";
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

	std::unordered_map<std::string,
		std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>> logicMap;
	std::unordered_set<std::string> procSet;
	std::unordered_set<std::string> stmtSet;
	std::unordered_set<std::string> stmtModifiesSet;
	std::unordered_set<std::string> stmtUsesSet;
	std::unordered_set<std::string> varSet;

	void createProcRef();
	void createStmtRef();
	void createStmtRefModifies();
	void createStmtRefUses();
	void createVarRef();

public:

	PQLRefConsistentLogic();

	~PQLRefConsistentLogic();

	bool hasRef(std::string relation, std::string leftType, std::string rightType);
};