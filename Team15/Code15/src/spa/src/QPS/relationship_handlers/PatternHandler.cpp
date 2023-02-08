
#include "PatternHandler.h"

PatternHandler::PatternHandler(PKB &pkb) : ClauseHandler(pkb){}

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

    // wildcard-wildcard
    if (leftType == Utility::UNDERSCORE) {
        set<string> allRHS; // = pkb.getAllPatternRHS()
        if (rightType == Utility::UNDERSCORE) {
            if (getResultFromPKB(pkb, patternType).empty()) {
                result.setResultTrue(false);
                return result;
            }
        } else if (rightType == Utility::UNDERSCORED_EXPR) {
            for (string RHSStr : allRHS) {

            }

        }

    } else if (leftType == Utility::SYNONYM) {

    } else if (leftType == Utility::QUOTED_IDENT) {

    } else {
        throw std::runtime_error("Unhandled left or right arg type in PatternHandler");
    }

    return result;
}