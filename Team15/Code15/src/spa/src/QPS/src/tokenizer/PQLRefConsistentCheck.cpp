#include "QPS/include/tokenizer/PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {

    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    std::vector<WithClause> withClauseVec = query.getWithClauseVec();

    std::multimap < std::string, std::string > varTable = query.getSynonymTable();
    PQLRefConsistentLogic* refConsistentLogic = new PQLRefConsistentLogic();
    bool isSuchThatFlag = true;
    bool isPatternFlag = true;

    for (SuchThatClause suchThatClause : suchThatClauseVec) {
        
        std::string refType = suchThatClause.getRelationShip();
        Relationship suchThatRefType = Utility::getRelationshipFromString(refType);
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getReferenceType(suchThatClause.getLeftArg());

        if (suchThatLeftType == Utility::synonym) {
            suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
        }

        std::string suchThatRightType = Utility::getReferenceType(suchThatClause.getRightArg());
        if (suchThatRightType == Utility::synonym) {
            suchThatRightType = varTable.find(suchThatRightVarName)->second;
        }

        if (suchThatRefType == PARENT || suchThatRefType == PARENT_STAR) {
            isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::parent, suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == FOLLOWS || suchThatRefType == FOLLOWS_STAR) {
            isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::follows , suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == MODIFIES) {
            if (suchThatLeftType == Utility::quoted_ident) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::modifiesP, suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::integer) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::modifiesS, suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::underscore) {
                isSuchThatFlag = false;
            }
            else if (suchThatLeftType == Utility::procedure) {
                //leftArg type is procedure		
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::modifiesP, suchThatLeftType, suchThatRightType);
            }
            else {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::modifiesS, suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == USES) {
            if (suchThatLeftType == Utility::quoted_ident) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::usesP, suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::integer) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::usesS, suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::underscore) {
                isSuchThatFlag = false;
            }
            else if (suchThatLeftType == Utility::procedure) {
                //leftArg type is procedure
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::usesP, suchThatLeftType, suchThatRightType);
            }
            else {
                isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::usesS, suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == CALLS || suchThatRefType == CALLS_STAR) {
            isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::calls , suchThatLeftType, suchThatRightType);
        }
        if (suchThatRefType == NEXT || suchThatRefType == NEXT_STAR) {
            isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::next, suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == AFFECTS || suchThatRefType == AFFECTS_STAR) {
            isSuchThatFlag = refConsistentLogic->hasRelationRef(Utility::affects, suchThatLeftType, suchThatRightType);
        }

        if (!isSuchThatFlag) {
            return false;
        }
    }
    for (PatternClause patternClause : patternClauseVec) {
        std::string patternSynonymName = patternClause.getPatternSynonym();
        std::string patternRefType = varTable.find(patternSynonymName)->second;
        DesignEntity enumPatternRefType = Utility::getDesignEntityFromString(patternRefType);
        isPatternFlag = enumPatternRefType == WHILE_ENTITY || enumPatternRefType == IF_ENTITY || enumPatternRefType == ASSIGN_ENTITY;
        if (!isPatternFlag) {
            return false;
        }

        // If firstArg is a synonym, it must be a variable synonym
        std::string firstArg = patternClause.getFirstArg();
        std::string firstArgType = Utility::getReferenceType(firstArg);
        if (firstArgType == Utility::synonym) {
            if (varTable.find(firstArg)-> second != Utility::variable) {
                return false;
            }
        }
    }
    for (WithClause withClause : withClauseVec) {
        
        bool isLeftAttrRef = withClause.isFirstArgAttrRef();
        bool isRightAttrRef = withClause.isSecondArgAttrRef();
        

        if (!isLeftAttrRef) {
            return false;
        }

        AttrRef leftAttrRef = withClause.getFirstArgAttrRef();
        std::string leftSynType = leftAttrRef.getSynType();
        std::string leftAttrName = leftAttrRef.getAttrName();

        if (isRightAttrRef) {
            AttrRef rightAttrRef = withClause.getSecondArgAttrRef();
            std::string rightSynType = rightAttrRef.getSynType();
            std::string rightAttrName = rightAttrRef.getAttrName();
            return refConsistentLogic->isWithRefCompatible(leftSynType, leftAttrName, rightSynType, rightAttrName);       
        }
        else {
            bool isRightValueIdent = withClause.isSecondArgIdent();
            bool isRightValueInt = withClause.isSecondArgInteger();
            std::string actualRightValueType = Utility::synonym;
            if (isRightValueIdent) {
                actualRightValueType = Utility::quoted_ident;
            }
            if (isRightValueInt) {
                actualRightValueType = Utility::integer;
            }
            // If leftSynType isn't paired with correct attribute name and corresponding value, return false.
            return refConsistentLogic->isWithRefCompatible(leftSynType, leftAttrName, actualRightValueType);
            
        }
    }
    return true;
}
