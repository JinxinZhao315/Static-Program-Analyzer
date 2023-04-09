#include <string>
#include <vector>
#include "Elem.h"
#include "qps/include/model/Clause.h"

#pragma once

class SelectClause : public Clause {
private:
    std::vector<Elem*> selectedElements;
public:
	SelectClause();

	SelectClause(std::vector<Elem*>& selectedElements);

	~SelectClause();

	std::vector<Elem*> getSelectedElements();
};