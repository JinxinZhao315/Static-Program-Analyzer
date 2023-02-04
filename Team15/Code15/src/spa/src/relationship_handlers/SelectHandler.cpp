#include "SelectHandler.h"

SelectHandler::SelectHandler(PKB pkb, ResultTable resultTable) : ClauseHandler(pkb, resultTable) {}

Result SelectHandler::evalSelect(SelectClause selectClause, std::multimap<std::string, std::string> varTable) {
    std::string varName = selectClause.getVarName();
    Result result;
    // Wildcard-Wildcard
    std::string varType = varTable.find(varName)->second;
    

    //returnVars = PKB.getEntity(varType);
    return result;

    // TODO: add other cases
    
}