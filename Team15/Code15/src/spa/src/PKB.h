#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "EntityTable.h"
#include "AbstractionTable.h"
#include "StatementTable.h"

using namespace std;

class PKB {
public:
	virtual void addProc(Procedure* proc);

	virtual void addStmt(Statement* stmt);

	virtual void addVar(Variable* var);

	virtual void addConst(Constant* constant);

	virtual void addFollows(Statement* leader, Statement* follower);

	virtual void addParent(Statement* parent, Statement* child);

	virtual void addStmtUsesVar(Statement* stmt, Variable* var);

	virtual void addProcUsesVar(Procedure* proc, Variable* var);

	virtual void addStmtModifiesVar(Statement* stmt, Variable* var);

	virtual void addProcModifiesVar(Procedure* proc, Variable* var);

	virtual Procedure* getProc(const ProcedureName& procName);

	virtual Statement* getStmt(const StatementNumber& stmtNum);

	virtual Variable* getVar(const VariableName& varName);

	virtual Constant* getConst(const ConstantName& constName);

	virtual unordered_set<ProcedureName> getAllProcNames();

	virtual unordered_set<StatementNumber> getAllStmtNums();

	virtual unordered_set<VariableName> getAllVarNames();

	virtual unordered_set<ConstantName> getAllConstNames();
};