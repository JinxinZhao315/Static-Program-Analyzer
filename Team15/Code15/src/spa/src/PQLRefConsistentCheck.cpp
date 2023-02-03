#include "PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {
    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    for (SuchThatClause suchThatClause : suchThatClauseVec) {
        std::multimap < std::string, std::string > varTable = query.getVarTable();
        // to do check whether integer or underscore(non synonym)
        std::string suchThatRefType = suchThatClause.getRelationShip();
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getPrimitiveType(suchThatClause.getLeftArg());

        if (suchThatLeftType == "synonym") {
            suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
        }

        std::string suchThatRightType = Utility::getPrimitiveType(suchThatClause.getRightArg());
        if (suchThatRightType == "synonym") {
            suchThatRightType = varTable.find(suchThatRightVarName)->second;
        }
        std::shared_ptr<PQLRefConsistentLogic> refConsistentLogic = std::make_shared<PQLRefConsistentLogic>();

        if (suchThatRefType == "Parent" || suchThatRefType == "Parent*") {
            return refConsistentLogic->hasRef("Parent", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Follows" || suchThatRefType == "Follows*") {
            return refConsistentLogic->hasRef("Follows", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Modifies") {
            if (suchThatLeftType == "quotedIdent") {
                return refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "integer") {
                return refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "underscore") {
                return false;
            }
            if (suchThatLeftType == "synonym" && varTable.find(suchThatLeftVarName)->second == "procedure") {
                //leftArg type is procedure		
                return refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else {
                return refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Uses") {
            if (suchThatLeftType == "quotedIdent") {
                return refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "integer") {
                return refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "underscore") {
                return false;
            }
            if (suchThatLeftType == "synonym" && varTable.find(suchThatLeftVarName)->second == "procedure") {
                //leftArg type is procedure
                return refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else {
                return refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            }
        }
    }
}

bool PQLRefConsistentCheck::checkSynonym() {
    return false;
}