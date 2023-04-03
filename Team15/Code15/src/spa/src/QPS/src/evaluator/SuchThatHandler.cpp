
#include "QPS/include/evaluator/SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(PKB &pkb) : ClauseHandler(pkb) {}

bool SuchThatHandler::getIsRelationshipSetEmpty(Relationship relationship, string type, string arg) {
    std::set<string> ret;

    switch (relationship) {
        case FOLLOWS:
            if (type == GET_LEADER) {
                int leader = pkb.getFollowsLeaderNum(stoi(arg), -1);
                return leader == -1;
            } else {
                int follower = pkb.getFollowsFollowerNum(stoi(arg), -1);
                return follower == -1;
            }
        case FOLLOWS_STAR:
            if (type == GET_LEADER) {
                return pkb.getFollowsStarLeaderNums(stoi(arg)).empty();
            } else {
                return pkb.getFollowsStarFollowerNums(stoi(arg)).empty();
            }
        case PARENT:
            if (type == GET_LEADER) {
                int parent = pkb.getParentParentNum(stoi(arg), -1);
                return parent == -1;
            }
            else {
                return pkb.getParentChildNums(stoi(arg)).empty();
            }
        case PARENT_STAR:
            if (type == GET_LEADER) {
                return pkb.getParentStarParentNums(stoi(arg)).empty();
            }
            else {
                return pkb.getParentStarChildNums(stoi(arg)).empty();
            }
        case CALLS:
            if (type == GET_LEADER) {
                return pkb.getCallsCallerNames(arg).empty();
            }
            else {
                return pkb.getCallsCalleeNames(arg).empty();
            }
        case CALLS_STAR:
            if (type == GET_LEADER) {
                return pkb.getCallsStarCallerNames(arg).empty();
            }
            else {
                return pkb.getCallsStarCalleeNames(arg).empty();
            }
        case NEXT:
            if (type == GET_LEADER) {
                return pkb.getPreviousStmtNums(stoi(arg)).empty();
            }
            else {
                return pkb.getNextStmtNums(stoi(arg)).empty();
            }
        case NEXT_STAR:
            if (type == GET_LEADER) {
                return pkb.getStarPreviousStmtNums(stoi(arg)).empty();
            }
            else {
                return pkb.getStarNextStmtNums(stoi(arg)).empty();
            }
        case AFFECTS:
            if (type == GET_LEADER) {
                return pkb.getAffectsModifierStmtNums(stoi(arg)).empty();
            }
            else {
                return pkb.getAffectsUserStmtNums(stoi(arg)).empty();
            }
        case AFFECTS_STAR:
            if (type == GET_LEADER) {
                return pkb.getAffectsStarModifierStmtNums(stoi(arg)).empty();
            }
            else {
                return pkb.getAffectsStarUserStmtNums(stoi(arg)).empty();
            }
        case USES_P:
            return  pkb.getUsesVarsFromProc(arg).empty();
        case USES_S:
            return pkb.getUsesVarsFromStmt(stoi(arg)).empty();
        case MODIFIES_S:
            return pkb.getModifiesVarsFromStmt(stoi(arg)).empty();
        case MODIFIES_P:
            return pkb.getModifiesVarsFromProc(arg).empty();
        default:
            throw PQLSyntaxError("Unknown relationship type");

    }

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


Result SuchThatHandler::evaluate(Relationship relationship, SuchThatClause suchThatClause,
    ResultTable& resultTable, std::multimap<std::string, std::string> &synonymTable, 
    int& synEvalPosition, std::vector<std::string>evalSynList) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();

    ReferenceType leftType = Utility::getEnumReferenceType(leftArg);
    ReferenceType rightType = Utility::getEnumReferenceType(rightArg);

    Result result;

    if (relationship == USES) {
        if (leftType == QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
            relationship = USES_P;
        } else {
            relationship = USES_S;
        }
    } else if (relationship == MODIFIES) {
        if (leftType == QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
            relationship = MODIFIES_P;
        } else {
            relationship = MODIFIES_S;
        }
    }

    // Wildcard-Wildcard
    if (leftType == UNDERSCORE && rightType == UNDERSCORE) {
        bool isEmpty = getIsPkbEmpty(relationship);
        if (isEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard - Quoted_ident
    else if (leftType == UNDERSCORE && rightType == QUOTED_IDENT) {
        if (getIsRelationshipSetEmpty(relationship, GET_LEADER, Utility::trim_double_quotes(rightArg))) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard-Int
    else if (leftType == UNDERSCORE && rightType == INTEGER) {
        if (getIsRelationshipSetEmpty(relationship, GET_LEADER, rightArg)) {
            result.setResultTrue(false);
            return result;
        }
    }

    // Quoted_ident - Wildcard
    else if (leftType == QUOTED_IDENT && rightType == UNDERSCORE) {
        if (getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, Utility::trim_double_quotes(leftArg))) {
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
        if (getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, leftArg)) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int-Int
    else if (leftType == INTEGER && rightType == INTEGER) {
        bool isInRelationship = getIsInRelationship(relationship, leftArg, rightArg);
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
        std::set<string> synValuesStrSet = resultTable.containsSyn(leftArg)
            ? resultTable.getSynValues(leftArg)
            : Utility::getResultFromPKB(pkb, synonDeType);
        //std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (rightType == UNDERSCORE) {
            for (auto currSynonVal: currSynonValues) {
                if (!getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, currSynonVal)) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        } else if (rightType == INTEGER || rightType == QUOTED_IDENT) {
            for (auto currSynonVal : currSynonValues) {
                bool isInRelationship = getIsInRelationship(relationship,
                                                            currSynonVal,
                                                            Utility::trim_double_quotes(rightArg));
                if (isInRelationship) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }

        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, leftArg));
    }
    // Wilcard / Int / Quoted-ident - Synon
    else if (leftType != SYNONYM && rightType == SYNONYM) {
        string synonDeType = synonymTable.find(rightArg)->second;
        std::set<string> synValuesStrSet = resultTable.containsSyn(rightArg)
            ? resultTable.getSynValues(rightArg)
            : Utility::getResultFromPKB(pkb, synonDeType);
        //std::set<string> synValuesStrSet = Utility::getResultFromPKB(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (leftType == UNDERSCORE) {
            for (auto currSynonVal : currSynonValues) {
                if (!getIsRelationshipSetEmpty(relationship, GET_LEADER, currSynonVal)) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (leftType == INTEGER || leftType == QUOTED_IDENT) {
            for (auto currSynonVal : currSynonValues) {
                bool isInRelationship = getIsInRelationship(relationship,
                                                            Utility::trim_double_quotes(leftArg),
                                                            currSynonVal);
                if (isInRelationship) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }

        if (resultSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }
        result.setClauseResult(ResultTable(resultSynonValues, rightArg));
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
        std::vector<std::string> synsToCheck = suchThatClause.getSynList();
        //no common syn in resultTable
        if (!resultTable.containsSyn(leftArg) && !resultTable.containsSyn(rightArg)) {
            std::set<string> leftSynValuesStrSet = Utility::getResultFromPKB(pkb, leftDeType);
            std::set<string> rightSynValuesStrSet = Utility::getResultFromPKB(pkb, rightDeType);
            std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
            std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());
            if (isSynLeftRightArgSame) {
                tempTable = ResultTable({ leftArg });
                for (int i = 0; i < currLeftValues.size(); i++) {
                    std::vector<std::string> tuple = std::vector{ currLeftValues[i]};
                    bool isInRelationship = getIsInRelationship(relationship, tuple[0], tuple[0]);
                    if (isInRelationship) {
                        tempTable.insertTuple(tuple);
                    }
                }
            }
            else {
                tempTable = ResultTable({ leftArg, rightArg });
                for (int i = 0; i < currLeftValues.size(); i++) {
                    for (int j = 0; j < currRightValues.size(); j++) {
                        std::vector<std::string> tuple = std::vector{ currLeftValues[i], currRightValues[j] };
                        bool isInRelationship = getIsInRelationship(relationship, tuple[0], tuple[1]);
                        if (isInRelationship) {
                            tempTable.insertTuple(tuple);
                        }
                    }
                }
            }
            //delete unnecessary synonym before merging
            removeUselessSyns(synsToCheck, tempTable, evalSynList, synEvalPosition);
            resultTable.combineTable(tempTable);
        }
        //both syns in resultTable, just filter the resultTable
        else if (resultTable.containsSyn(leftArg) && resultTable.containsSyn(rightArg)) {
            tempTable = ResultTable(resultTable.getSynList());
            std::vector<std::string> resultTableSynList = resultTable.getSynList();
            std::vector<std::string>::iterator it = std::find(resultTableSynList.begin(), resultTableSynList.end(), leftArg);
            int leftSynIndex = it - resultTableSynList.begin();
            it = std::find(resultTableSynList.begin(), resultTableSynList.end(), rightArg);
            int rightSynIndex = it - resultTableSynList.begin();
            for (int i = 0; i < resultTable.getColNum(); i++) {
                std::vector<std::string> tuple = resultTable.getTuple(i);
                bool isInRelationship = getIsInRelationship(relationship, tuple[leftSynIndex], tuple[rightSynIndex]);
                if (isInRelationship) {
                    tempTable.insertTuple(tuple);
                }
            }
            resultTable = tempTable;
            removeUselessSyns(synsToCheck, tempTable, evalSynList, synEvalPosition);
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
            std::vector<std::string>::iterator it = std::find(resultTableSynList.begin(), resultTableSynList.end(), synInTable);
            int synInTableIndex = it - resultTableSynList.begin();
            std::set<std::string> synOutsideTableSet = Utility::getResultFromPKB(pkb, synOutsideTableType);
            std::vector<std::string> synOutsideTableVec(synOutsideTableSet.begin(), synOutsideTableSet.end());

            for (int i = 0; i < resultTable.getColNum(); i++) {
                std::vector<std::string> tuple = resultTable.getTuple(i);
                for (int j = 0; j < synOutsideTableVec.size(); j++) {
                    bool isInRelationship;
                    if (resultTable.containsSyn(leftArg)) {
                        isInRelationship = getIsInRelationship(relationship, tuple[synInTableIndex], synOutsideTableVec[j]);
                    }
                    else {
                        isInRelationship = getIsInRelationship(relationship, synOutsideTableVec[j], tuple[synInTableIndex]);
                    }
                    
                    if (isInRelationship) {
                        tempTable.insertTuple(Utility::mergeTuple(tuple, { synOutsideTableVec[j] }, {-1}));
                    }
                }
            }
            resultTable = tempTable;
            removeUselessSyns(synsToCheck, resultTable, evalSynList, synEvalPosition);
        }
            
        if (resultTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        /*result.setClauseResult(tempTable);*/
    }


    else {
        throw PQLSyntaxError("Unhandled left or right arg type in SuchThatHandler");
    }

    return result;
}