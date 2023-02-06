#include <string>
#include <vector>

#pragma once

class SelectClause {
private:
    std::string varName;
public:
	SelectClause();

	SelectClause(std::string varName);

	~SelectClause();

	std::string getVarName();
};