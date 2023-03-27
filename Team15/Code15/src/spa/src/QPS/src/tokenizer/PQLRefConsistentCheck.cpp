#include "QPS/include/tokenizer/PQLRefConsistentCheck.h"

PQLRefConsistentCheck::PQLRefConsistentCheck() {}

PQLRefConsistentCheck::~PQLRefConsistentCheck() {}

bool PQLRefConsistentCheck::checkPQLRefConsistent(Query query) {

    std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    std::vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
    std::vector<WithClause> withClauseVec = query.getWithClauseVec();

    std::multimap < std::string, std::string > varTable = query.getSynonymTable();
    //race condition when multithreads?
    //std::shared_ptr<PQLRefConsistentLogic> refConsistentLogic = std::make_shared<PQLRefConsistentLogic>();
    PQLRefConsistentLogic* refConsistentLogic = new PQLRefConsistentLogic();
    bool isSuchThatFlag = true;
    bool isPatternFlag = true;

    for (SuchThatClause suchThatClause : suchThatClauseVec) {
        
        // to do check whether integer or underscore(non synonym)
        std::string suchThatRefType = suchThatClause.getRelationShip();
        std::string suchThatLeftVarName = suchThatClause.getLeftArg();
        std::string suchThatRightVarName = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getReferenceType(suchThatClause.getLeftArg());
        //ReferenceType suchThatLeftType = Utility::getEnumReferenceType(suchThatClause.getLeftArg());
       /* std::string leftType;
        std::string rightType;
        switch (suchThatLeftType)
        {
        case SYNONYM: {
            leftType = varTable.find(suchThatLeftVarName)->second;
            break;
        }
            
        default:
            break;
        }
        ReferenceType suchThatRightType = Utility::getEnumReferenceType(suchThatClause.getRightArg());
        switch (suchThatRightType)
        {
        case SYNONYM: {
            rightType = varTable.find(suchThatRightVarName)->second;
            break;
        }

        default:
            break;
        }*/
        if (suchThatLeftType == Utility::synonym) {
            suchThatLeftType = varTable.find(suchThatLeftVarName)->second;
        }

        std::string suchThatRightType = Utility::getReferenceType(suchThatClause.getRightArg());
        if (suchThatRightType == Utility::synonym) {
            suchThatRightType = varTable.find(suchThatRightVarName)->second;
        }
        
        //Relationship relationship = Utility::getRelationshipFromString(suchThatRefType);
       /* switch (relationship)
        {
        case MODIFIES:
            break;
        case USES:
            break;
        case CALLS:
            break;
        case CALLSSTAR:
            break;
        case AFFECTS:
            break;
        case AFFECTSSTAR:
            break;
        case NEXT:
            break;
        case NEXTSTAR:
            break;
        case PARENT:
        case PARENTSTAR:
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Parent", leftType, rightType);
            break;
        case FOLLOWS:
            break;
        case FOLLOWSSTAR:
            break;
        default:
            break;
        }*/
        if (suchThatRefType == "Parent" || suchThatRefType == "Parent*") {
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Parent", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Follows" || suchThatRefType == "Follows*") {
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Follows", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Modifies") {
            if (suchThatLeftType == Utility::quoted_ident) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::integer) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::underscore) {
                isSuchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure		
                isSuchThatFlag = refConsistentLogic->hasRelationRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Uses") {
            if (suchThatLeftType == Utility::quoted_ident) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::integer) {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("UsesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::underscore) {
                isSuchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure
                isSuchThatFlag = refConsistentLogic->hasRelationRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else {
                isSuchThatFlag = refConsistentLogic->hasRelationRef("UsesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Calls" || suchThatRefType == "Calls*") {
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Calls", suchThatLeftType, suchThatRightType);
        }
        if (suchThatRefType == "Next" || suchThatRefType == "Next*") {
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Next", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Affects" || suchThatRefType == "Affects*") {
            isSuchThatFlag = refConsistentLogic->hasRelationRef("Affects", suchThatLeftType, suchThatRightType);
        }

        if (!isSuchThatFlag) {
            return false;
        }
    }
    for (PatternClause patternClause : patternClauseVec) {
        std::string patternSynonymName = patternClause.getPatternSynonym();
        std::string patternRefType = varTable.find(patternSynonymName)->second;
        isPatternFlag = patternRefType == "while" || patternRefType == "if" || patternRefType == "assign";
        if (!isPatternFlag) {
            return false;
        }

        // If firstArg is a synonym, it must be a variable synonym
        std::string firstArg = patternClause.getFirstArg();
        std::string firstArgType = Utility::getReferenceType(firstArg);
        if (firstArgType == Utility::synonym) {
            if (varTable.find(firstArg)-> second != "variable") {
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
