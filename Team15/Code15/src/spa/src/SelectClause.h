#include <string>
#include "PQLConstants.h"
#include "AbstractClause.h"
#include "vector"

#pragma once

class SelectClause: AbstractClause {
private:
	std::vector<std::string> selectVector;
public:
	SelectClause(std::string varName, std::string entity);

	~SelectClause();

	std::pair <std::string, std::string> getVarEntityPair();

	void ModifyFirst(std::string varName);

	void ModifySecond(std::string entity);
};