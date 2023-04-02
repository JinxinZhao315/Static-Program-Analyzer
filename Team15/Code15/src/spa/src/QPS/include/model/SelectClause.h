#include <string>
#include <vector>
#include "Elem.h"
#include "QPS/include/model/Clause.h"

#pragma once

class SelectClause : public Clause {
private:
    std::vector<Elem> synNames;
public:
	SelectClause();

	SelectClause(std::vector<Elem> synNames);

	~SelectClause();

	std::vector<Elem> getSynNameVec();
};