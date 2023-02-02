#include <string>
#include <vector>

#pragma once

class SelectClause {
private:
    // std::vector<std::string> selectVector;
    std::string varName;
    std::string entity;
public:
	SelectClause();

	SelectClause(std::string varName, std::string entity);

	~SelectClause();

	std::pair <std::string, std::string> getVarEntityPair();

	void modifyVarName(std::string varName);

	void modifyEntity(std::string entity);
};