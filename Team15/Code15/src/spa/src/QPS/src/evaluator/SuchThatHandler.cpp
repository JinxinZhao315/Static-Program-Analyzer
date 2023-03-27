
#include "QPS/include/evaluator/SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(PKB &pkb) : ClauseHandler(pkb) {}

bool SuchThatHandler::getIsRelationshipSetEmpty(string relationship, string type, string arg) {
    std::set<string> ret;

    if (relationship == "Follows") {
        if (type == GET_LEADER) {
            int leader = pkb.getFollowsLeaderNum(stoi(arg), -1);
            return leader == -1;
        } else {
            int follower = pkb.getFollowsFollowerNum(stoi(arg), -1);
            return follower == -1;
        }
    } else if (relationship == "Follows*"){
        if (type == GET_LEADER) {
            return pkb.getFollowsStarLeaderNums(stoi(arg)).empty();
        } else {
            return pkb.getFollowsStarFollowerNums(stoi(arg)).empty();
        }
    }  else if (relationship == "Parent") {
        if (type == GET_LEADER) {
            int parent = pkb.getParentParentNum(stoi(arg), -1);
            return parent == -1;
        }
        else {
            std::set<int> children = pkb.getParentChildNums(stoi(arg));
            return children.empty();

        }
    } else if (relationship == "Parent*") {
        if (type == GET_LEADER) {
            return pkb.getParentStarParentNums(stoi(arg)).empty();
        }
        else {
            return pkb.getParentStarChildNums(stoi(arg)).empty();
        }
    }  else if (relationship == "Calls") {
        if (type == GET_LEADER) {
            return pkb.getCallsCallerNames(arg).empty();
        }
        else {
            return pkb.getCallsCalleeNames(arg).empty();
        }
    }
    else if (relationship == "Calls*"){
        if (type == GET_LEADER) {
            return pkb.getCallsStarCallerNames(arg).empty();
        }
        else {
            return pkb.getCallsStarCalleeNames(arg).empty();
        }
    }


    else if (relationship == "Next") {
        if (type == GET_LEADER) {
            return pkb.getPreviousStmtNums(stoi(arg)).empty();
        }
        else {
            return pkb.getNextStmtNums(stoi(arg)).empty();
        }
    }
    else if (relationship == "Next*") {
        if (type == GET_LEADER) {
            return pkb.getStarPreviousStmtNums(stoi(arg)).empty();
        }
        else {
            return pkb.getStarNextStmtNums(stoi(arg)).empty();
        }
    } else if (relationship == "UsesP") {
        return  pkb.getUsesVarsFromProc(arg).empty();
    } else if (relationship == "UsesS") {
        return pkb.getUsesVarsFromStmt(stoi(arg)).empty();
    } else if (relationship == "ModifiesS") {
        return pkb.getModifiesVarsFromStmt(stoi(arg)).empty();
    } else if (relationship == "ModifiesP") {
        return pkb.getModifiesVarsFromProc(arg).empty();
    }

    else {
        throw PQLSyntaxError("Unknown relationship type");
    }

}

bool SuchThatHandler:: getIsInRelationship(string relationship, string leftArg, string rightArg) {

    if (relationship == "Follows*") {
        return pkb.areInFollowsStarRelationship(stoi(leftArg), stoi(rightArg));
    } else if (relationship == "Follows") {
        return pkb.areInFollowsRelationship(stoi(leftArg), stoi(rightArg));
    }  else  if (relationship == "Parent*") {
        return pkb.areInParentStarRelationship(stoi(leftArg), stoi(rightArg));
    } else if (relationship == "Parent"){
        return pkb.areInParentRelationship(stoi(leftArg), stoi(rightArg));
    }  else if (relationship == "Next*") {
        return pkb.areInNextStarRelationship(stoi(leftArg), stoi(rightArg));
    } else if (relationship == "Next"){
        return pkb.areInNextRelationship(stoi(leftArg), stoi(rightArg));
    } else  if (relationship == "Calls*") {
        return pkb.areInCallsStarRelationship(leftArg, rightArg);
    } else if (relationship == "Calls"){
        return pkb.areInCallsRelationship(leftArg, rightArg);
    } else if (relationship == "UsesP") {
        return pkb.areInUsesProcRelationship(leftArg, rightArg);
    } else if (relationship == "UsesS") {
        return pkb.areInUsesStmtRelationship(stoi(leftArg), rightArg);
    } else if (relationship == "ModifiesS") {
        return pkb.areInModifiesStmtRelationship(stoi(leftArg), rightArg);
    } else if (relationship == "ModifiesP") {
        return pkb.areInModifiesProcRelationship(leftArg, rightArg);
    }


    else {
        throw PQLSyntaxError("Unknown relationship type");
    }

}


bool SuchThatHandler:: getIsPkbEmpty(string relationship) {
    if (relationship == "Follows" || relationship == "Follows*") {
        return pkb.isFollowsEmpty();
    } else if (relationship == "Parent" || relationship == "Parent*") {
        return  pkb.isParentEmpty();
    }  else  if (relationship == "Next*") {
        return pkb.isNextStarEmpty();
    } else if (relationship == "Next"){
        return pkb.isNextEmpty();
    }  else if (relationship == "Calls*") {
        return pkb.isCallsStarEmpty();
    } else if (relationship == "Calls"){
        return pkb.isCallsEmpty();
    }

    else {
        throw PQLSyntaxError("Unknown relationship type");
    }
}


Result SuchThatHandler::evaluate(string relationship, SuchThatClause suchThatClause,
                                 std::multimap<std::string, std::string> &synonymTable) {
    std::string leftArg = suchThatClause.getLeftArg();
    std::string rightArg = suchThatClause.getRightArg();
    std::string leftType = Utility::getReferenceType(leftArg);
    std::string rightType = Utility::getReferenceType(rightArg);
    Result result;

    if (relationship == "Uses") {
        if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
            relationship = "UsesP";
        } else {
            relationship = "UsesS";
        }
    } else if (relationship == "Modifies") {
        if (leftType == Utility::QUOTED_IDENT || (synonymTable.find(leftArg) != synonymTable.end() && synonymTable.find(leftArg)->second == "procedure")) {
            relationship = "ModifiesP";
        } else {
            relationship = "ModifiesS";
        }
    }

    // Wildcard-Wildcard
    if (leftType == Utility::UNDERSCORE && rightArg == Utility::UNDERSCORE) {
        bool isEmpty = getIsPkbEmpty(relationship);
        if (isEmpty) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard - Quoted_ident
    else if (leftType == Utility::UNDERSCORE && rightType == Utility::QUOTED_IDENT) {
        if (getIsRelationshipSetEmpty(relationship, GET_LEADER, Utility::trim_double_quotes(rightArg))) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Quoted_ident - Wildcard
    else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::UNDERSCORE) {
        if (getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, Utility::trim_double_quotes(leftArg))) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Quoted_ident - Quoted_ident
    else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
        bool isInRelationship = getIsInRelationship(relationship, Utility::trim_double_quotes(leftArg), Utility::trim_double_quotes(rightArg));
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Wildcard-Int
    else if (leftType == Utility::UNDERSCORE && rightType == Utility::INTEGER) {
        if (getIsRelationshipSetEmpty(relationship, GET_LEADER, rightArg)) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int-Wildcard
    else if (leftType == Utility::INTEGER && rightType == Utility::UNDERSCORE) {
        if (getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, leftArg)) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int-Int
    else if (leftType == Utility::INTEGER && rightType == Utility::INTEGER) {
        bool isInRelationship = getIsInRelationship(relationship, leftArg, rightArg);
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Int - Quoted_ident
    else if (leftType == Utility::INTEGER && rightType == Utility::QUOTED_IDENT) {
        bool isInRelationship = getIsInRelationship(relationship, leftArg, Utility::trim_double_quotes(rightArg));
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }

    // Quoted-ident - Quoted-ident
    else if (leftType == Utility::QUOTED_IDENT && rightType == Utility::QUOTED_IDENT) {
        bool isInRelationship = getIsInRelationship(relationship,
                                           Utility::trim_double_quotes(leftArg),
                                           Utility::trim_double_quotes(rightArg));
        if (!isInRelationship) {
            result.setResultTrue(false);
            return result;
        }
    }
    // Synon - Wilcard / Int / Quoted-ident
    else if (leftType == Utility::SYNONYM && rightType != Utility::SYNONYM) {
        string synonDeType = synonymTable.find(leftArg)->second;
        std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (rightType == Utility::UNDERSCORE) {
            for (auto currSynonVal: currSynonValues) {
                if (!getIsRelationshipSetEmpty(relationship, GET_FOLLOWER, currSynonVal)) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        } else if (rightType == Utility:: INTEGER || rightType == Utility::QUOTED_IDENT) {
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
    else if (leftType != Utility::SYNONYM && rightType == Utility::SYNONYM) {
        string synonDeType = synonymTable.find(rightArg)->second;
        std::set<string> synValuesStrSet = Utility::getFullSetFromPkb(pkb, synonDeType);
        std::vector<std::string> currSynonValues(synValuesStrSet.begin(), synValuesStrSet.end());
        std::vector<std::string> resultSynonValues;

        if (leftType == Utility::UNDERSCORE) {
            for (auto currSynonVal : currSynonValues) {
                if (!getIsRelationshipSetEmpty(relationship, GET_LEADER, currSynonVal)) {
                    resultSynonValues.push_back(currSynonVal);
                }
            }
        }
        else if (leftType == Utility::INTEGER || leftType == Utility::QUOTED_IDENT) {
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
    else if (leftType == Utility::SYNONYM && rightType == Utility::SYNONYM) {
        if (leftArg == rightArg) {
            result.setResultTrue(false);
            return result;
        }
        std::string leftDeType = synonymTable.find(leftArg)->second;
        std::string rightDeType = synonymTable.find(rightArg)->second;

        std::set<string> leftSynValuesStrSet = Utility::getFullSetFromPkb(pkb, leftDeType);
        std::set<string> rightSynValuesStrSet = Utility::getFullSetFromPkb(pkb, rightDeType);

        std::vector<std::string> currLeftValues(leftSynValuesStrSet.begin(), leftSynValuesStrSet.end());
        std::vector<std::string> currRightValues(rightSynValuesStrSet.begin(), rightSynValuesStrSet.end());


        ResultTable initTable(currLeftValues, leftArg);
        initTable.combineTable(ResultTable(currRightValues, rightArg));
        int initTableSize = initTable.getColNum();
        ResultTable tempTable({ leftArg, rightArg });


        for (int i = 0; i < initTableSize; i++) {
            std::vector<std::string> tuple = initTable.getTuple(i);
            bool isInRelationship = getIsInRelationship(relationship, tuple[0], tuple[1]);
            if (isInRelationship) {
                tempTable.insertTuple({ tuple[0], tuple[1] });
            }
        }

        if (tempTable.isTableEmpty()) {
            result.setResultTrue(false);
            return result;
        }

        result.setClauseResult(tempTable);
    }


    else {
        throw PQLSyntaxError("Unhandled left or right arg type in SuchThatHandler");
    }

    return result;
}