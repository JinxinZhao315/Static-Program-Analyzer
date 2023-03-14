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
            suchThatFlag = refConsistentLogic->hasRelationRef("Parent", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Follows" || suchThatRefType == "Follows*") {
            suchThatFlag = refConsistentLogic->hasRelationRef("Follows", suchThatLeftType, suchThatRightType);
        }

        if (suchThatRefType == "Modifies") {
            if (suchThatLeftType == Utility::QUOTED_IDENT) {
                suchThatFlag = refConsistentLogic->hasRelationRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::INTEGER) {
                suchThatFlag = refConsistentLogic->hasRelationRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::UNDERSCORE) {
                suchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure		
                suchThatFlag = refConsistentLogic->hasRelationRef("ModifiesP", suchThatLeftType, suchThatRightType);
            }
            else {
                suchThatFlag = refConsistentLogic->hasRelationRef("ModifiesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Uses") {
            if (suchThatLeftType == Utility::QUOTED_IDENT) {
                suchThatFlag = refConsistentLogic->hasRelationRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::INTEGER) {
                suchThatFlag = refConsistentLogic->hasRelationRef("UsesS", suchThatLeftType, suchThatRightType);
            }
            else if (suchThatLeftType == Utility::UNDERSCORE) {
                suchThatFlag = false;
            }
            else if (suchThatLeftType == "procedure") {
                //leftArg type is procedure
                suchThatFlag = refConsistentLogic->hasRelationRef("UsesP", suchThatLeftType, suchThatRightType);
            }
            else {
                suchThatFlag = refConsistentLogic->hasRelationRef("UsesS", suchThatLeftType, suchThatRightType);
            }
        }
        if (suchThatRefType == "Calls" || suchThatRefType == "Calls*") {
            suchThatFlag = refConsistentLogic->hasRelationRef("Calls", suchThatLeftType, suchThatRightType);
        }
        if (suchThatRefType == "Next" || suchThatRefType == "Next*") {
            suchThatFlag = refConsistentLogic->hasRelationRef("Next", suchThatLeftType, suchThatRightType);
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

        // If firstArg is a synonym, it must be a variable synonym
        std::string firstArg = patternClause.getFirstArg();
        std::string firstArgType = Utility::getReferenceType(firstArg);
        if (firstArgType == Utility::SYNONYM) {
            if (varTable.find(firstArg)-> second != "variable") {
                return false;
            }
        }
    }
    for (WithClause withClause : withClauseVec) {
        Ref withLeftArg = withClause.getFirstArg();
        Ref withRightArg = withClause.getSecondArg();
        bool isLeftAttrRef = withLeftArg.isRefAttrRef();
        bool isRightAttrRef = withRightArg.isRefAttrRef();

        if (!isLeftAttrRef || isRightAttrRef) {
            return false;
        }

        AttrRef leftAttrRef = withLeftArg.getAttrRef();
        AttrRef rightAttrRef = withRightArg.getAttrRef();
        std::string leftType = leftAttrRef.getSynType();
        leftAttrRef.getAttrName()
            isValidWith();
        // If firstArg is proc
        if (firstArg) {

        }
            
    }
    return true;
}
