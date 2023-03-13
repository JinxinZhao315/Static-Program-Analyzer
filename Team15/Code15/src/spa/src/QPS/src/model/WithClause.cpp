#include "../../include/model/WithClause.h"

WithClause::WithClause() {}

WithClause::WithClause(Ref firstArg, Ref rightArg) {
	this->leftArg = firstArg;
	this->rightArg = rightArg;
}

WithClause::~WithClause() {}

Ref WithClause::getFirstArg() {
	return this->firstArg;
}

Ref WithClause::getSecondArg() {
	return this->secondArg;
}