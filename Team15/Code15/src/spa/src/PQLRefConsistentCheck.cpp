#include "PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}
std::string PQLRefConsistentCheck::getPrimitiveType(std::string varName) { return ""; }

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {
    //<<<<<<< HEAD
    //	SuchThatClause suchThatClause = query.getSuchThatClause();
    //	std::multimap < std::string, std::string > varTable = query.getVarTable();
    //	// to do check whether integer or underscore(non synonym)
    //	std::string suchThatRefType = suchThatClause.getRelationShip();
    //	std::string suchThatLeftVarName = suchThatClause.getLeftPair().second;
    //	std::string suchThatRightVarName = suchThatClause.getRightPair().second;
    //	std::string suchThatLeftType = suchThatClause.getLeftPair().first;
    //	if (suchThatLeftType == "synonym") {//7--isValidSynonym -> varTable.find(suchThatLeftArg)
    //		suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
    //	}
    //	
    //	std::string suchThatRightType = suchThatClause.getRightPair().first;
    //	if (suchThatRightType == "synonym") {
    //		suchThatRightType = varTable.find(suchThatRightVarName)->second;
    //	}
    //=======

    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    for (SuchThatClause suchThatClause : suchThatClauseVec) {
        std::multimap < std::string, std::string > varTable = query.getVarTable();
        // to do check whether integer or underscore(non synonym)
        std::string suchThatRefType = suchThatClause.getRelationShip();
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = getPrimitiveType(suchThatClause.getLeftArg());
        //>>>>>>> f580dd7df14cdcf2e70fb0e14d84babefc1b089e


        //<<<<<<< HEAD
        //	std::shared_ptr<PQLRefConsistentLogic> refConsistentLogic = std::make_shared<PQLRefConsistentLogic>();
        //=======
        std::string suchThatRightType = getPrimitiveType(suchThatClause.getRightArg());
        if (suchThatRightType == "synonym") {
            suchThatRightType = varTable.find(suchThatRightVarName)->second;
        }
        std::shared_ptr<PQLRefConsistentLogic> refConsistentLogic = std::make_shared<PQLRefConsistentLogic>();
        //>>>>>>> f580dd7df14cdcf2e70fb0e14d84babefc1b089e

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

            //<<<<<<< HEAD
            //	}
            //	if (suchThatRefType == "Uses") {
            //		if (suchThatLeftType == "indent_string") {
            //			return refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            //		}
            //		if (suchThatLeftType == "integer") {
            //			return refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            //		}
            //		if (suchThatLeftType == "_") {
            //			return false;
            //		}
            //		if (suchThatLeftType == "procedure") {
            //			//leftArg type is procedure		
            //			return refConsistentLogic->hasRef("UsesP", suchThatLeftType, suchThatRightType);
            //		}
            //		else {
            //			return refConsistentLogic->hasRef("UsesS", suchThatLeftType, suchThatRightType);
            //		}
            //	}
            //
            //=======
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
        //>>>>>>> f580dd7df14cdcf2e70fb0e14d84babefc1b089e
    }
}

bool PQLRefConsistentCheck::checkSynonym() {
	return false;
}