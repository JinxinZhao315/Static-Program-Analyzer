#include "SelectHandler.h"

SelectHandler::SelectHandler(PKB &pkb) : 
    ClauseHandler(pkb), pkb(pkb), resultTable(resultTable){}

std::string SelectHandler::evalSelect(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable) {
    std::string varName = selectClause.getVarName();
    std::string varType = varTable.find(varName)->second;
    Result result;
    result.setLeftArg(varName, ClauseHandler::getResultFromPKB(this->pkb, varType));
    ClauseHandler::combineResult(resultTable, result);

    // Put every variable name selected in selectClause into ResultTable keys,
    // and add full set of possible values of that variable into ResultTable values.
    // return vector of return variables
    return varName;
    
}