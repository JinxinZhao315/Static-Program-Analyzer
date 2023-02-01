#include <unordered_map>
#include <string>
#include <set>

class SemanticLogic {
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
		std::pair<std::set<std::string>, std::set<std::string>>> LogicMap;

public:

	SemanticLogic();

	~SemanticLogic();
	std::set<std::string> createProc_Ref();
	std::set<std::string> createStmt_Ref();
	std::set<std::string> createVar_Ref();
	std::set<std::string> createStmt_Ref_Modifies();
	std::set<std::string> createStmt_Ref_Uses();
	std::set<std::string> createSemanticMap();

};