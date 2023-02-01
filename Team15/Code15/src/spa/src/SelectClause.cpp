#include "SelectClause.h"

SelectClause::SelectClause() {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::string varName, std::string entity) {
	selectVector.push_back(varName);
	selectVector.push_back(entity);
}

void SelectClause::ModifyFirst(std::string varName) {
	varName = varName;
}

void SelectClause::ModifySecond(std::string entity) {
	entity = entity;
}

std::pair <std::string, std::string> SelectClause::getVarEntityPair() {
	return std::pair <std::string, std::string>(selectVector[0], selectVector[1]);
}
