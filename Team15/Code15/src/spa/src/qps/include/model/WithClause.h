#include "Ref.h"
#include "qps/include/model/Clause.h"

#pragma once

class WithClause : public Clause{
private:
	Ref firstArg;
	Ref secondArg;
public:
	WithClause();
	WithClause(Ref firstArg, Ref secondArg);
	~WithClause();

	AttrRef getFirstArgAttrRef();
	AttrRef getSecondArgAttrRef();
	std::string getFirstArgConstValue();
	std::string getSecondArgConstValue();

	bool isFirstArgAttrRef();
	bool isSecondArgAttrRef();
	bool isFirstArgIdent();
	bool isSecondArgIdent();
	bool isFirstArgInteger();
	bool isSecondArgInteger();

}; 