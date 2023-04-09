
#include "qps/include/evaluator/SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(PKB &pkb) : ClauseHandler(pkb) {}

bool SuchThatHandler::getIsRelationshipSetEmpty(Relationship relationship, string type, string arg) {
    return getRelationshipSet(relationship, type, arg).empty();
}

bool SuchThatHandler:: getIsInRelationship(Relationship relationship, string leftArg, string rightArg) {

    switch(relationship) {
        case FOLLOWS_STAR:
            return pkb.areInFollowsStarRelationship(stoi(leftArg), stoi(rightArg));
        case FOLLOWS:
            return pkb.areInFollowsRelationship(stoi(leftArg), stoi(rightArg));
        case PARENT_STAR:
            return pkb.areInParentStarRelationship(stoi(leftArg), stoi(rightArg));
        case PARENT:
            return pkb.areInParentRelationship(stoi(leftArg), stoi(rightArg));
        case NEXT_STAR:
            return pkb.areInNextStarRelationship(stoi(leftArg), stoi(rightArg));
        case NEXT:
            return pkb.areInNextRelationship(stoi(leftArg), stoi(rightArg));
        case CALLS_STAR:
            return pkb.areInCallsStarRelationship(leftArg, rightArg);
        case CALLS:
            return pkb.areInCallsRelationship(leftArg, rightArg);
        case USES_P:
            return pkb.areInUsesProcRelationship(leftArg, rightArg);
        case USES_S:
            return pkb.areInUsesStmtRelationship(stoi(leftArg), rightArg);
        case MODIFIES_S:
            return pkb.areInModifiesStmtRelationship(stoi(leftArg), rightArg);
        case MODIFIES_P:
            return pkb.areInModifiesProcRelationship(leftArg, rightArg);
        case AFFECTS_STAR:
            return pkb.areInAffectsStarRelationship(stoi(leftArg), stoi(rightArg));
        case AFFECTS:
            return pkb.areInAffectsRelationship(stoi(leftArg), stoi(rightArg));
        default:
            throw PQLSyntaxError("Unknown relationship type");

    }


}

std::set<std::string> SuchThatHandler::getRelationshipSet(Relationship relationship, string type, string arg) {
    switch (relationship) {
    case FOLLOWS:
        if (type == GET_LEADER) {
            int leader = pkb.getFollowsLeaderNum(stoi(arg), -1);
            return leader == -1 ? std::set<std::string>{} : std::set<std::string>{ std::to_string(leader) };
        }
        else {
            int follower = pkb.getFollowsFollowerNum(stoi(arg), -1);
            return follower == -1 ? std::set<std::string>{} : std::set<std::string>{ std::to_string(follower) };
        }
    case FOLLOWS_STAR:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getFollowsStarLeaderNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getFollowsStarFollowerNums(stoi(arg)));
        }
    case PARENT:
        if (type == GET_LEADER) {
            int parent = pkb.getParentParentNum(stoi(arg), -1);
            return parent == -1 ? std::set<std::string>{} : std::set<std::string>{ std::to_string(parent) };
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getParentChildNums(stoi(arg)));
        }
    case PARENT_STAR:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getParentStarParentNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getParentStarChildNums(stoi(arg)));
        }
    case CALLS:
        if (type == GET_LEADER) {
            return pkb.getCallsCallerNames(arg);
        }
        else {
            return pkb.getCallsCalleeNames(arg);
        }
    case CALLS_STAR:
        if (type == GET_LEADER) {
            return pkb.getCallsStarCallerNames(arg);
        }
        else {
            return pkb.getCallsStarCalleeNames(arg);
        }
    case NEXT:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getPreviousStmtNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getNextStmtNums(stoi(arg)));
        }
    case NEXT_STAR:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getStarPreviousStmtNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getStarNextStmtNums(stoi(arg)));
        }
    case AFFECTS:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getAffectsModifierStmtNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getAffectsUserStmtNums(stoi(arg)));
        }
    case AFFECTS_STAR:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getAffectsStarModifierStmtNums(stoi(arg)));
        }
        else {
            return Utility::convertIntSetToStrSet(pkb.getAffectsStarUserStmtNums(stoi(arg)));
        }
    case USES_P:
        if (type == GET_LEADER) {
            return  pkb.getUsesProcsFromVar(arg);
        }
        else {
            return pkb.getUsesVarsFromProc(arg);
        }
        
    case USES_S:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getUsesStmtsFromVar(arg));
        }
        else {
            return pkb.getUsesVarsFromStmt(stoi(arg));
        }
    case MODIFIES_S:
        if (type == GET_LEADER) {
            return Utility::convertIntSetToStrSet(pkb.getModifiesStmtsFromVar(arg));
        }
        else {
            return pkb.getModifiesVarsFromStmt(stoi(arg));
        }
        
    case MODIFIES_P:
        if (type == GET_LEADER) {
            return  pkb.getModifiesProcsFromVar(arg);
        }
        else {
            return  pkb.getModifiesVarsFromProc(arg);
        }
    default:
        throw PQLSyntaxError("Unknown relationship type");

    }
}

bool SuchThatHandler:: getIsPkbEmpty(Relationship relationship) {
    switch (relationship) {
        case FOLLOWS:
            return pkb.isFollowsEmpty();
        case FOLLOWS_STAR:
            return pkb.isFollowsStarEmpty();
        case PARENT:
            return pkb.isParentEmpty();
        case PARENT_STAR:
            return  pkb.isParentStarEmpty();
        case NEXT_STAR:
            return pkb.isNextStarEmpty();
        case NEXT:
            return pkb.isNextEmpty();
        case CALLS_STAR:
            return pkb.isCallsStarEmpty();
        case CALLS:
            return pkb.isCallsEmpty();
        case AFFECTS_STAR:
            return pkb.isAffectsStarEmpty();
        case AFFECTS:
            return pkb.isAffectsEmpty();
        default:
            throw PQLSyntaxError("Unknown relationship type");

    }

}
void SuchThatHandler::clearPkbTable(Relationship relationship) {
    switch (relationship)
    {
        case AFFECTS:
            pkb.clearAffects();
            break;
        case AFFECTS_STAR:
            pkb.clearAffectsStar();
            break;
        case NEXT_STAR:
            pkb.clearNextStar();
            break;
        default:
            break;
    }
}

Result SuchThatHandler::evaluate(Relationship relationship, SuchThatClause suchThatClause,
    ResultTable& resultTable, std::multimap<std::string, std::string> &synonymTable, 
    int& synEvalPosition, std::vector<std::string>evalSynList) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();

    ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
    ReferenceType rightType = Utility::getEnumReferenceType(rightArg);

    Result result;

    if (relationship == USES) {
        if (leftType == QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == Utility::procedure)) {
            relationship = USES_P;
        } else {
            relationship = USES_S;
        }
    } 
    else if (relationship == MODIFIES) {
        if (leftType == QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == Utility::procedure)) {
            relationship = MODIFIES_P;
        } else {
            relationship = MODIFIES_S;
        }
    }

    // Wildcard-Wildcard
    if (leftType == UNDERSCORE && rightType == UNDERSCORE) {
        bool isEmpty = getIsPkbEmpty(relationship);

        clearPkbTable(relationship); 

        if (isEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard - Quoted_ident
    else if (leftType == UNDERSCORE && rightType == QUOTED_IDENT) {
        bool isRelationshipEmpty = getIsRelationshipSetEmpty(relationship, GET_LEADER, Utility::trim_double_quotes(rightArg));
        if (isRelationshipEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard-Int
    else if (leftType == UNDERSCORE && rightType == INTEGER) {
        bool isRelationshipEmpty = getIsRelationshipSetEmpty(relationship, GET_LEADER, rightArg);
        
        clearPkbTable(relationship);

        if (isRelationshipEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }

    // Quoted_ident - Wildcard
    else if (leftType == QUOTED_IDENT && rightType == UNDERSCORE) {
        bool isRelationshipEmpty = getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, Utility::trim_double_quotes(leftArg));
        if (isRelationshipEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Quoted_ident - Quoted_ident
    else if (leftType == QUOTED_IDENT && rightType == QUOTED_IDENT) {
        bool isInRelationship = getIsInRelationship(relationship,
                                                    Utility::trim_double_quotes(leftArg),
                                                    Utility::trim_double_quotes(rightArg));
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }

    // Int-Wildcard
    else if (leftType == INTEGER && rightType == UNDERSCORE) {
        bool isRelationshipEmpty = getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, leftArg);
        
        clearPkbTable(relationship);

        if (isRelationshipEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int-Int
    else if (leftType == INTEGER && rightType == INTEGER) {
        bool isInRelationship = getIsInRelationship(relationship, leftArg, rightArg);
        clearPkbTable(relationship);
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int - Quoted_ident
    else if (leftType == INTEGER && rightType == QUOTED_IDENT) {
        bool isInRelationship = getIsInRelationship(relationship, leftArg, Utility::trim_double_quotes(rightArg));

        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }

    // Synon - Wilcard / Int / Quoted-ident
    else if (leftType == SYNONYM && rightType != SYNONYM) {
        string synonDeType = synonymTable.find(leftArg)->second;
        ResultTable tempTable;
        if (rightType == UNDERSCORE) {
            //if syn is in resultTable, just do a filtering in existing tuples
            if (resultTable.containsSyn(leftArg)) {
                //construct tempTable and find the index of this syn, valid tuple will be inserted into tempTable
                std::vector<std::string> resultTableSynList = resultTable.getSynList();
                tempTable = ResultTable(resultTableSynList);
                int synIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), leftArg) - resultTableSynList.begin();
                std::set<std::string> candidateSynVals = resultTable.getSynValues(leftArg);
                std::unordered_set<std::string> validSynVals;
                //two for loop to reduce the number of calls to pkb which takes longer time
                for (std::string synVal : candidateSynVals) {
                    if (!getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, synVal)) {
                        validSynVals.insert(synVal);
                    }
                }
                for (int i = 0; i < resultTable.getTupleNum(); i++) {
                    std::vector<std::string> tuple = resultTable.getTuple(i);
                    if (validSynVals.count(tuple[synIndex]) == 1) {
                        tempTable.insertTuple(tuple);
                    }
                }
                //if no syn values satisfy the condition, set the result to false
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                //remove syns not used in later clauses
                removeUselessSyns({ leftArg }, tempTable, evalSynList, synEvalPosition);
                resultTable = tempTable;
            }
            //syn is not in resultTable, get candidate syn values from pkb
            else {
                std::vector<std::string> resultSynVals;
                std::set<string> candidateSynVals = Utility::getResultFromPKB(pkb, synonDeType);
                for (std::string synVal : candidateSynVals) {
                    if (!getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, synVal)) {
                        resultSynVals.push_back(synVal);
                    }
                }
                tempTable = ResultTable(resultSynVals, leftArg);
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ leftArg }, tempTable, evalSynList, synEvalPosition);
                resultTable.combineTable(tempTable);
            }
            
        } 
        else if (rightType == INTEGER || rightType == QUOTED_IDENT) {
            if (resultTable.containsSyn(leftArg)) {
                tempTable = ResultTable(resultTable.getSynList());
                std::vector<std::string> resultTableSynList = resultTable.getSynList();
                int synIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), leftArg) - resultTableSynList.begin();
                for (int i = 0; i < resultTable.getTupleNum(); i++) {
                    std::vector<std::string> tuple = resultTable.getTuple(i);
                    if (getIsInRelationship(relationship, tuple[synIndex], Utility::trim_double_quotes(rightArg))) {
                        tempTable.insertTuple(tuple);
                    }
                }
                if (tempTable.isTableEmpty() && !tempTable.isSynListEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ leftArg }, tempTable, evalSynList, synEvalPosition);
                resultTable = tempTable;
            }
            else {
                std::vector<std::string> resultSynVals;
                std::set<string> candidateSynVals = Utility::getResultFromPKB(pkb, synonDeType);
                for (std::string currSynonVal : candidateSynVals) {
                    if (getIsInRelationship(relationship,currSynonVal,Utility::trim_double_quotes(rightArg))) {
                        resultSynVals.push_back(currSynonVal);
                    }
                }
                tempTable = ResultTable(resultSynVals, leftArg);
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ leftArg }, tempTable, evalSynList, synEvalPosition);
                resultTable.combineTable(tempTable);
            }
        }

        clearPkbTable(relationship);

        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wilcard / Int / Quoted-ident - Synon
    else if (leftType != SYNONYM && rightType == SYNONYM) {
        string synonDeType = synonymTable.find(rightArg)->second;
        ResultTable tempTable;
        if (leftType == UNDERSCORE) {
            if (resultTable.containsSyn(rightArg)) {
                tempTable = ResultTable(resultTable.getSynList());
                std::vector<std::string> resultTableSynList = resultTable.getSynList();
                int synIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), rightArg) - resultTableSynList.begin();
                std::unordered_set<std::string> validSynVals;
                std::set<string> candidateSynVals = Utility::getResultFromPKB(pkb, synonDeType);
                //loop through candidate syn vals to find valid vals
                for (std::string synVal : candidateSynVals) {
                    if (!getIsRelationshipSetEmpty(relationship, GET_LEADER, synVal)) {
                        validSynVals.insert(synVal);
                    }
                }
                //for each tuple in resultTable, check if it contains valid syn vals
                for (int i = 0; i < resultTable.getTupleNum(); i++) {
                    std::vector<std::string> tuple = resultTable.getTuple(i);
                    if (validSynVals.count(tuple[synIndex]) == 1) {
                        tempTable.insertTuple(tuple);
                    }
                }
                //if no syn values satisfy the condition, set the result to false
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ rightArg }, tempTable, evalSynList, synEvalPosition);
                resultTable = tempTable;
            }
            else {
                std::vector<std::string> resultSynVals;
                std::set<string> candidateSynVals = Utility::getResultFromPKB(pkb, synonDeType);
                for (std::string synVal : candidateSynVals) {
                    if (!getIsRelationshipSetEmpty(relationship, GET_LEADER, synVal)) {
                        resultSynVals.push_back(synVal);
                    }
                }
                tempTable = ResultTable(resultSynVals, rightArg);
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ rightArg }, tempTable, evalSynList, synEvalPosition);
                resultTable.combineTable(tempTable);
            }
        }
        else if (leftType == INTEGER || leftType == QUOTED_IDENT) {
            if (resultTable.containsSyn(rightArg)) {
                tempTable = ResultTable(resultTable.getSynList());
                std::vector<std::string> resultTableSynList = resultTable.getSynList();
                int synIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), rightArg) - resultTableSynList.begin();
                for (int i = 0; i < resultTable.getTupleNum(); i++) {
                    std::vector<std::string> tuple = resultTable.getTuple(i);
                    if (getIsInRelationship(relationship, Utility::trim_double_quotes(leftArg), tuple[synIndex])) {
                        tempTable.insertTuple(tuple);
                    }
                }
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ rightArg }, tempTable, evalSynList, synEvalPosition);
                resultTable = tempTable;
            }
            else {
                std::vector<std::string> resultSynVals;
                std::set<string> candidateSynVals = Utility::getResultFromPKB(pkb, synonDeType);
                for (std::string currSynonVal : candidateSynVals) {
                    if (getIsInRelationship(relationship, Utility::trim_double_quotes(leftArg), currSynonVal)) {
                        resultSynVals.push_back(currSynonVal);
                    }
                }
                tempTable = ResultTable(resultSynVals, rightArg);
                if (tempTable.isTableEmpty()) {
                    result.setResultTrue(false);
                    return result;
                }
                removeUselessSyns({ rightArg }, tempTable, evalSynList, synEvalPosition);
                resultTable.combineTable(tempTable);
            }
        }

        clearPkbTable(relationship);

        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Synon - Synon
    else if (leftType == SYNONYM && rightType == SYNONYM) {
        bool isSynLeftRightArgSame = false;
        if (leftArg == rightArg) {
            isSynLeftRightArgSame = true;
        }
        std::string leftDeType = synonymTable.find(leftArg)->second;
        std::string rightDeType = synonymTable.find(rightArg)->second;
        ResultTable tempTable;
        std::vector<std::string> synsToCheck = {leftArg, rightArg};
        //no common syn in resultTable
        if (!resultTable.containsSyn(leftArg) && !resultTable.containsSyn(rightArg)) {
            std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
            std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
            //left syn and right syn are same
            if (isSynLeftRightArgSame) {
                tempTable = ResultTable({ leftArg });
                for (std::string leftVal : leftSynValuesStrSet) {
                    bool isInRelationship = getIsInRelationship(relationship, leftVal, leftVal);
                    if (isInRelationship) {
                        std::vector<std::string> tuple = std::vector{ leftVal };
                        tempTable.insertTuple(tuple);
                    }
                }
            }
            //left and right are different syn
            else {
                tempTable = ResultTable({ leftArg, rightArg });
                for (std::string leftVal : leftSynValuesStrSet) {
                    std::set<std::string>followers = getRelationshipSet(relationship, GET_FOLLOWER, leftVal);
                    std::vector<std::string> synVals;
                    //rightSynValuesStrSet contains all the syn value of this type, 
                    //followers contains all the syn value that satisfy the constraint, nlogn for intersection, O(n * nlogn)
                    std::set_intersection(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end(), followers.begin(), followers.end(), std::back_inserter(synVals));
                    for (std::string rightVal : synVals) {
                        std::vector<std::string> tuple = std::vector{ leftVal, rightVal };
                        tempTable.insertTuple(tuple);
                    }
                }
            }
            if (tempTable.isTableEmpty()) {
                result.setResultTrue(false);
                return result;
            }
            //delete unnecessary synonym before merging
            removeUselessSyns(synsToCheck, tempTable, evalSynList, synEvalPosition);
            resultTable.combineTable(tempTable);
        }
        //both syns in resultTable, just filter the resultTable
        else if (resultTable.containsSyn(leftArg) && resultTable.containsSyn(rightArg)) {
            tempTable = ResultTable(resultTable.getSynList());
            std::vector<std::string> resultTableSynList = resultTable.getSynList();
            int leftSynIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), leftArg) - resultTableSynList.begin();
            int rightSynIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), rightArg) - resultTableSynList.begin();
            for (int i = 0; i < resultTable.getTupleNum(); i++) {
                std::vector<std::string> tuple = resultTable.getTuple(i);
                bool isInRelationship = getIsInRelationship(relationship, tuple[leftSynIndex], tuple[rightSynIndex]);
                if (isInRelationship) {
                    tempTable.insertTuple(tuple);
                }
            }
            if (tempTable.isTableEmpty()) {
                result.setResultTrue(false);
                return result;
            }
            resultTable = tempTable;
            removeUselessSyns(synsToCheck, resultTable, evalSynList, synEvalPosition);
        }
        //one syn is in resultTable but another one not
        else {
            std::vector<std::string> resultTableSynList = resultTable.getSynList();
            std::vector<std::string> tempSynList = resultTableSynList;
            std::string synInTable;
            std::string synOutsideTable;
            std::string synOutsideTableType;
            if (resultTable.containsSyn(leftArg)) {
                synInTable = leftArg;
                synOutsideTable = rightArg;
                synOutsideTableType = rightDeType;
                tempSynList.push_back(rightArg);
            }
            else {
                synInTable = rightArg;
                synOutsideTable = leftArg;
                synOutsideTableType = leftDeType;
                tempSynList.push_back(leftArg);
            }
            tempTable = ResultTable(tempSynList);
            int synInTableIndex = std::find(resultTableSynList.begin(), resultTableSynList.end(), synInTable) - resultTableSynList.begin();
            std::set<std::string> synOutsideTableSet = Utility::getResultFromPKB(pkb, synOutsideTableType);
            //find tuple that satisfy the constraint
            for (int i = 0; i < resultTable.getTupleNum(); i++) {
                std::vector<std::string> tuple = resultTable.getTuple(i);
                std::vector<std::string>synVals;
                if (resultTable.containsSyn(leftArg)) {
                    std::set<std::string> followers = getRelationshipSet(relationship, GET_FOLLOWER, tuple[synInTableIndex]);
                    std::set_intersection(synOutsideTableSet.begin(), synOutsideTableSet.end(), followers.begin(), followers.end(), std::back_inserter(synVals));
                }
                else {
                    std::set<std::string> leader = getRelationshipSet(relationship, GET_LEADER, tuple[synInTableIndex]);
                    std::set_intersection(synOutsideTableSet.begin(), synOutsideTableSet.end(), leader.begin(), leader.end(), std::back_inserter(synVals));
                }
                for (std::string synOutside : synVals) {
                    tempTable.insertTuple(Utility::mergeTuple(tuple, { synOutside }, { -1 }));
                }
            }

            clearPkbTable(relationship);

            if (tempTable.isTableEmpty()) {
                result.setResultTrue(false);
                return result;
            }
            resultTable = tempTable;
            removeUselessSyns(synsToCheck, resultTable, evalSynList, synEvalPosition);
        }

        if (resultTable.isTableEmpty() && !resultTable.isSynListEmpty()) {
            result.setResultTrue(false);
            return result;
        }
    }

    else {
    throw PQLSyntaxError("Unhandled left or right arg type in SuchThatHandler");
    }

    return result;
}