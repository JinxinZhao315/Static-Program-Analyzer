#include "QPS/include/model/WithClause.h"

WithClause::WithClause() {}

WithClause::WithClause(Ref firstArg, Ref rightArg) {
	this->firstArg = firstArg;
	this->secondArg = rightArg;
}

WithClause::~WithClause() {}

AttrRef WithClause::getFirstArgAttrRef() {
	return this->firstArg.getAttrRef();
}

AttrRef WithClause::getSecondArgAttrRef() {
	return this->secondArg.getAttrRef();
}

//get fixed ident or integer value
std::string WithClause::getFirstArgConstValue() {
	if (this->firstArg.isRefIdent()) {
		return this->firstArg.getIdentValue();
	} else if (this->firstArg.isRefInteger()){
		return this->firstArg.getIntegerValue();
	}
	else {
		return "";
	}
}

std::string WithClause::getSecondArgConstValue() {
	if (this->secondArg.isRefIdent()) {
		return this->secondArg.getIdentValue();
	}
	else if (this->secondArg.isRefInteger()) {
		return this->secondArg.getIntegerValue();
	}
	else {
		return "";
	}
}

bool WithClause::isFirstArgAttrRef() {
	return this->firstArg.isRefAttrRef();
}

bool WithClause::isSecondArgAttrRef() {
	return this->secondArg.isRefAttrRef();
}