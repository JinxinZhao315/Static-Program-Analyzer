#include "Ref.h"

#pragma once

class WithClause {
private:
	Ref firstArg;
	Ref secondArg;
public:
	WithClause();
	WithClause(Ref firstArg, Ref secondArg);
	~WithClause();
	Ref getFristArg();
	Ref getSecondArg();
}; 