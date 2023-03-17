#include <string>
#include <vector>
#include "Elem.h"

#pragma once

class SelectClause {
private:
    std::vector<Elem> synNames;
public:
	SelectClause();

	SelectClause(std::vector<Elem> synNames);

	~SelectClause();

	std::vector<Elem> getSynNameVec();
};