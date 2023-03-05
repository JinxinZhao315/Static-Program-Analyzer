#include "QPS/include/tokenizer/PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {

    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    std::multimap < std::string, std::string > varTable = query.getSynonymTable();
    //race condition when multithreads?
    //std::shared_ptr<PQLRefConsistentLogic> refConsistentLogic = std::make_shared<PQLRefConsistentLogic>();
    PQLRefConsistentLogic* refConsistentLogic = new PQLRefConsistentLogic();
    bool suchThatFlag = true;
    bool patternFlag = true;

    for (SuchThatClause suchThatClause : suchThatClauseVec) {
        
        // to do check whether integer or underscore(non synonym)
        std::string suchThatRefType = suchThatClause.getRelationShip();
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getReferenceType(suchThatClause.getLeftArg());

        if (suchThatLeftType == Utility::SYNONYM) {
            suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
        }

        std::string suchThatRightType = Utility::getReferenceType(suchThatClause.getRightArg());
        if (suchThatRightType == Utility::SYNONYM) {
            suchThatRightType = varTable.find(suchThatRightVarName)->second;
        }
        

        if (suchThatRefType == "Parent" || suchThatRefType == "Parent*") {
            suchThatFlag = refConsistentLogic->hasRef("Parent", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Follows" || suchThatRefType == "Follows*") {
            suchThatFlag = refConsistentLogic->hasRef("Follows", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Modifies") {
            if (suchThatLeftType == Utility::QUOTED_IDENT) {
                suchThatFlag = refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::INTEGER) {
                suchThatFlag = refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::UNDERSCORE) {
                suchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure		
                suchThatFlag = refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else {
                suchThatFlag = refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Uses") {
            if (suchThatLeftType == Utility::QUOTED_IDENT) {
                suchThatFlag = refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::INTEGER) {
                suchThatFlag = refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::UNDERSCORE) {
                suchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure
                suchThatFlag = refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else {
                suchThatFlag = refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatFlag == false) {
            return false;
        }
    }
    for (PatternClause patternClause : patternClauseVec) {
        std::string patternSynonymName = patternClause.getPatternSynonym();
        std::string patternRefType = varTable.find(patternSynonymName)->second;
        patternFlag = patternRefType == "while" || patternRefType == "if" || patternRefType == "assign";
        if (patternFlag == false) {
            return false;
        }
    }

    return true;
}
