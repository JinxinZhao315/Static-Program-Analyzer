#include <string>
#include <vector>

#pragma once

class SelectClause {
private:
    std::vector<std::string> synNames;
public:
	SelectClause();

	SelectClause(std::string synName);

	SelectClause(std::vector<std::string> synNames);

	~SelectClause();

	std::vector<std::string> getSynNameVec();
};