//
// Created by Jinxin Zhao on 2/2/23.
//

#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(PKB pkb) {
    this->pkb = pkb;
}

std::string PQLEvaluator::evaluate(Query query) {
    ResultTable resultTable = ResultTable();

   std::multimap<std::string, std::string> varTable = query.getVarTable();

   // resultTable.insert({varName, std::set<std::string>()});
   SelectClause selectClause = query.getSelectClause();
   std::string returnSynons = parseSelectClause(selectClause, varTable, pkb, resultTable);

   std::vector<SuchThatClause> suchThatVec = query.getSuchThatClauseVec();
   std::vector<PatternClause> patternVec = query.getPatternClauseVec();

   for (SuchThatClause suchThatCl: suchThatVec) {
       std::string relationship = suchThatCl.getRelationShip();
       if (relationship == "Follows" || relationship == "Follows*") {
           FollowsHandler followsHandler = FollowsHandler(pkb, resultTable);
           //evalFollows return true/false
           Result result = followsHandler.evalFollows(suchThatCl);
       }
   }

   for (PatternClause patternCl: patternVec) {

   }

   // TODO: return the values of the selected synonym in ResultTable
	return "";
}

// TODO: finish this function
std::string PQLEvaluator::parseSelectClause(SelectClause selectClause, std::multimap<std::string, std::string> varTable, PKB &pkb, ResultTable& resultTable) {
    std::string varName = selectClause.getVarName();
    std::string varType = varTable.find(varName)->second;
    Result result;
    result.setLeftArg(varName, getResultFromPKB(pkb, varType));
    //combineResult(resultTable, result);
    
    // Put every variable name selected in selectClause into ResultTable keys,
    // and add full set of possible values of that variable into ResultTable values.
    // return vector of return variables
    return varName;
}

std::set<std::string> getResultFromPKB(PKB& pkb, std::string resultType) {
    std::set<std::string> temp;
    if (resultType == "constant") {
        //convertVecToSet(pkb.getConstants());
        return temp;
    }
    else if (resultType == "procedure") {
        //pkb.getProcedures();
        return temp;
    }
    else if (resultType == "variable") {
        //pkb.getVariables();
        return temp;
    }
    else {
        //pkb.getEntities(resultType);
        return temp;
    }
}

template <typename T>
std::set<T> convertVecToSet(std::vector<T> vec) {
    std::set<T> resultSet;
    for (T t : vec) {
        resultSet.insert(t);
    }
    return resultSet;
}