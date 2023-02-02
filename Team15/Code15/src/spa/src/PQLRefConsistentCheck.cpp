#include "PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {
	SuchThatClause suchThatClause = query.getSuchThatClause();
	std::multimap < std::string, std::string > varTable = query.getVarTable();
	// to do check whether integer or underscore(non synonym)
	std::string suchThatRefType = suchThatClause.getRelationShip();
	std::string suchThatLeftVarName = suchThatClause.getLeftPair().second;
	std::string suchThatRightVarName = suchThatClause.getRightPair().second;
	std::string suchThatLeftType = suchThatClause.getLeftPair().first;
	if (suchThatLeftType == "synonym") {//7--isValidSynonym -> varTable.find(suchThatLeftArg)
		suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
	}
	
	std::string suchThatRightType = suchThatClause.getRightPair().first;
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
		if (suchThatLeftType == "ident_string") {
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
		if (suchThatLeftType == "ident_string") {
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

bool PQLRefConsistentCheck::checkSynonym() {
	return false;
}