#include "QPS/include/evaluator/SelectHandler.h"

SelectHandler::SelectHandler(PKB& pkb) : ClauseHandler(pkb){}

std::string SelectHandler::evalSelect(SelectClause selectClause, std::multimap<std::string, std::string>& varTable, ResultTable& resultTable) {
    std::string varName = selectClause.getVarName();
    std::string varType = varTable.find(varName)->second;
    //Result result;
    resultTableCheckAndAdd(varName, resultTable, varType);
    
    //std::set<std::string> resultSet = ClauseHandler::getResultFromPKB(this->pkb, varType);
    //std::unordered_map<std::string, SynonymLinkageMap> intermediateResult;
    //for (std::string key : resultSet) {
    //    intermediateResult.insert(std::make_pair<>(key, SynonymLinkageMap()));
    //}
    //result.setFirstArg(varName, intermediateResult);

    //ClauseHandler::combineResult(resultTable, result);

    // Put every variable name selected in selectClause into ResultTable keys,
    // and add full set of possible values of that variable into ResultTable values.
    // return vector of return variables
    return varName;  
}