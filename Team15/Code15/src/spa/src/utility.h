#include <string>
#include <regex>
#include <unordered_set>
#include"exceptions/PQLSyntaxError.h"

namespace Utility{
	std::unordered_set<std::string> designEntitySet = { "procedure", "stmt", "read", "print", 
		"assign", "call", "while", "if" "variable", "constant" };
	std::unordered_set<std::string> relationshipSet{ "Follows",
		"Follows*", "Parent", "Parent*", "Uses", "Modifies" };
	std::string synonymFormat = "[a-zA-Z][a-zA-Z0-9]*";
	std::string integerFormat = "[1-9][0-9]*";
	std::string quotedIdentFormat = "\"[a-zA-Z][a-zA-Z0-9]*\"";
	std::string underscoredExpr = "_\"[\\s\\S]*\"_";
	std::string expr = "\"[\\s\\S]*\"";
	std::string underscore = "_";

	std::string extractKeyword(std::string input);

	std::string trim(std::string input);

	std::string getPrimitiveType(std::string input);
}