#include <set>
#include <string>
#include "PKB.h"

#pragma once

class PKBStub : public PKB {
public:
	std::set<std::string> constSet;
	std::set<std::string> varNameSet;
	std::set<int> stmtNumberByType;
	std::set<int> stmtNums;
	std::set<std::string> getAllConstVals();
	std::set<std::string> getAllVarNames();
	std::set<int> getAllStmtNumsByType(std::string type);
	std::set<int> getAllStmtNums();

};
