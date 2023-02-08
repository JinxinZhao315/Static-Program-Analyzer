
#include "PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}

set<string> PatternHandler::findMatchingLines(set<pair<string, int>> allRHS, string strToMatch) {
    set <string> ret;
    for (pair<string, int> retPair : allRHS) {
        string RHSStr = retPair.first;
        int lineNum = retPair.second;
        // TODO: matching
    }
    // Return set<string> of matching line numbers
    return ret;

}

Result PatternHandler::evalPattern(PatternClause patternClause, ResultTable &resultTable,
                                   std::multimap<std::string, std::string> &synonymTable) {

    string patternSynon = patternClause.getPatternSynonym();
    string leftArg = patternClause.getLeftArg();
    string rightArg = patternClause.getRightArg();
    string leftType = Utility::getReferenceType(leftArg);
    string rightType = Utility::getReferenceType(rightArg);
    Result result;
    string patternType = synonymTable.find(patternSynon)->second;
    resultTableCheckAndAdd(patternSynon, resultTable, patternType);

    // Does the Design Entity represented by the pattern synon exist in PKB?
    // If not, set result to false
    if (resultTable.getValueFromKey(patternSynon).empty()) {
        result.setResultTrue(false);
        return result;
    }


    if (leftType == Utility::UNDERSCORE) {

        if (rightType == Utility::UNDERSCORE) {

            return result;

        } else if (rightType == Utility::UNDERSCORED_EXPR) {

            set<pair<string, int>> allRHS; // = pkb.getAllPatternRHS()
            set<string> matchingLines = findMatchingLines(allRHS, rightArg);
            if (matchingLines.empty()) {
                result.setResultTrue(false);
                return result;
            }
            // TODO: add values to pattern synon

        }

    } else if (leftType == Utility::SYNONYM) {

        string leftDeType = synonymTable.find(leftArg)->second;
        resultTableCheckAndAdd(leftArg, resultTable, leftDeType);
        std::set<string> currSynonValues = resultTable.getValueFromKey(leftArg);

        // Does the Design Entity type represented by left synonym exist in PKB?
        // If not, set result to false
        if (currSynonValues.empty()) {
            result.setResultTrue(false);
            return result;
        }

        if (rightType == Utility::UNDERSCORE) {

            return result;

        } else if (rightType == Utility::UNDERSCORED_EXPR) {
                std::set<string> resultSynonValues;
                for (string currLeftVal: currSynonValues) {
                    set<pair<string, int>> matchingRHS; // = pkb.getPatternRHS(currLeftVal)
                    set<string> matchingLines = findMatchingLines(matchingRHS, rightArg);
                    if (matchingLines.empty()) {
                        result.setResultTrue(false);
                        return result;
                    }
                    // TODO: add values to pattern synon in result table
                }
        }

    } else if (leftType == Utility::QUOTED_IDENT) {

        // Do SIMPLE expressions with LHS == stated leftArg exist in PKB?
        // If not, set result to false
        set<pair<string, int>> matchingRHS; // = pkb.getPatternRHS(leftArg)

        if (matchingRHS.empty()) {
            result.setResultTrue(false);
            return result;
        }

        if (rightType == Utility::UNDERSCORE) {

            return result;

        } else if (rightType == Utility::UNDERSCORED_EXPR) {
            set<string> matchingLines = findMatchingLines(matchingRHS, rightArg);
            if (matchingLines.empty()) {
                result.setResultTrue(false);
                return result;
            }
            // TODO: add values to pattern synon

        }

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}