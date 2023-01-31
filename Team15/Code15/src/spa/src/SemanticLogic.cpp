#include "SemanticLogic.h"

SemanticLogic::SemanticLogic() {
}

SemanticLogic::~SemanticLogic() {
}

std::set<std::string> SemanticLogic::createProc_Ref() {
	std::set<std::string> procRefSet;
	procRefSet.insert(PROCEDURE);
	procRefSet.insert(INDENT_STRING);
	return procRefSet;
}
std::set<std::string> SemanticLogic::createStmt_Ref() {

}
std::set<std::string> SemanticLogic::createVar_Ref() {

}
std::set<std::string> SemanticLogic::createStmt_Ref_Modifies() {

}
std::set<std::string> SemanticLogic::createStmt_Ref_Uses() {

}

std::set<std::string> SemanticLogic::createSemanticMap() {

}

bool checkLogic() {

}