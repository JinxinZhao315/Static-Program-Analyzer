#include <string>
#include <vector>

#pragma once

class SelectClause {
private:
	std::vector<std::string> selectVector;
public:
	SelectClause();

	SelectClause(std::string varName, std::string entity);

	~SelectClause();

	std::pair <std::string, std::string> getVarEntityPair();

	void ModifyFirst(std::string varName);

	void ModifySecond(std::string entity);
};