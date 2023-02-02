#include "PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}
std::string PQLRefConsistentCheck::getPrimitiveType(std::string varName) { return ""; }

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {

    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    for (SuchThatClause suchThatClause: suchThatClauseVec) {
        std::multimap < std::string, std::string > varTable = query.getVarTable();
        // to do check whether integer or underscore(non synonym)
        std::string suchThatRefType = suchThatClause.getRelationShip();
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = getPrimitiveType(suchThatClause.getLeftArg());

        if (suchThatLeftType == "synonym") {
            suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
        }

        std::string suchThatRightType = getPrimitiveType(suchThatClause.getRightArg());
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
            if (suchThatLeftType == "indent_string") {
                return refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "integer") {
                return refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "_") {
                return false;
            }
            if (suchThatLeftType == "procedure") {
                //leftArg type is procedure
                return refConsistentLogic->hasRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else {
                return refConsistentLogic->hasRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }

        }
        if (suchThatRefType == "Uses") {
            if (suchThatLeftType == "indent_string") {
                return refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "integer") {
                return refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            }
            if (suchThatLeftType == "_") {
                return false;
            }
            if (suchThatLeftType == "procedure") {
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