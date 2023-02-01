#include "SelectClause.h"

SelectClause::SelectClause() {}

SelectClause::~SelectClause() {}

SelectClause::SelectClause(std::string varName, std::string entity) {
	this->varName = varName;
	this->entity = entity;
}

void SelectClause::ModifyVarName(std::string varName) {
	varName = varName;
}

void SelectClause::ModifyEntity(std::string entity) {
	entity = entity;
}

std::pair <std::string, std::string> SelectClause::getVarEntityPair() {
	return std::pair <std::string, std::string>(this->varName, this->entity);

}
