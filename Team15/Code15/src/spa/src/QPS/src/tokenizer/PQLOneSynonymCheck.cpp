#include "QPS/include/tokenizer/PQLOneSynonymCheck.h"

PQLOneSynonymCheck::PQLOneSynonymCheck() {

}

PQLOneSynonymCheck::~PQLOneSynonymCheck() {

}

bool PQLOneSynonymCheck::checkPQLOneSynonym(Query query) {
	std::multimap<std::string, std::string> varTable = query.getSynonymTable();
    std::vector<Clause*> clauseList = query.getClauseList();

    // All the synonyms used in clauses must be declared exactly once.
	for (auto iter = varTable.begin(); iter != varTable.end(); iter++) {
		if (varTable.count(iter->first) != 1) {
			return false;
		}
	}
    for (Clause *clause : clauseList) {
        switch (clause->getType())
        {
        case SUCH_THAT: {
            SuchThatClause* suchThatClause = (static_cast<SuchThatClause*>(clause));
            std::string suchThatLeftArg = suchThatClause->getLeftArg();
            std::string suchThatRightArg = suchThatClause->getRightArg();
            ReferenceType suchThatLeftType = Utility::getEnumReferenceType(suchThatLeftArg);
            ReferenceType suchThatRightType = Utility::getEnumReferenceType(suchThatRightArg);
            switch (suchThatLeftType)
            {
            case SYNONYM: {
                if (varTable.count(suchThatLeftArg) != 1) {
                    return false;
                }
                break;
            }
            default:
                break;
            }
            switch (suchThatRightType)
            {
            case SYNONYM: {
                if (varTable.count(suchThatRightArg) != 1) {
                    return false;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case PATTERN: {
            PatternClause* patternClause = (static_cast<PatternClause*>(clause));
            std::string patternSynonym = patternClause->getPatternSynonym();
            std::string patternFirstArg = patternClause->getFirstArg();
            ReferenceType patternSynonymType = Utility::getEnumReferenceType(patternSynonym);
            ReferenceType patternFirstType = Utility::getEnumReferenceType(patternFirstArg);
            switch (patternSynonymType)
            {
            case SYNONYM: {
                if (varTable.count(patternSynonym) != 1) {
                    return false;
                }
                break;
            }
            default:
                break;
            }
            switch (patternFirstType)
            {
            case SYNONYM: {
                if (varTable.count(patternFirstArg) != 1) {
                    return false;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case WITH: {
            WithClause* withClause = (static_cast<WithClause*>(clause));
            if (withClause->isFirstArgAttrRef()) {
                AttrRef firstAttrRef = withClause->getFirstArgAttrRef();
                std::string firstArg = firstAttrRef.getSynName();
                if (varTable.count(firstArg) != 1) {
                    return false;
                }
            }
            if (withClause->isSecondArgAttrRef()) {
                AttrRef secondAttrRef = withClause->getSecondArgAttrRef();
                std::string secondArg = secondAttrRef.getSynName();
                if (varTable.count(secondArg) != 1) {
                    return false;
                }
            }
            break;
        }
        case SELECT: {
            SelectClause* selectClause = (static_cast<SelectClause*>(clause));
            std::vector<Elem*> elemVec = selectClause->getSelectedElements();
            int elemVecSize = elemVec.size();
            for (Elem* elem : elemVec) {
                std::string elemSynName = elem->getSynName();
                if (elemVecSize > 1) {
                    if (varTable.count(elemSynName) != 1) { //multiple synonyms, can't be BOOLEAN, so each syn must appear exactly once
                        return false;
                    }
                }
                else {
                    if (elemSynName == Utility::boolean && varTable.count(elemSynName) > 1) { //if single syn and BOOLEAN, count can be 0 or 1
                        return false;
                    }
                    else if (elemSynName != Utility::boolean && varTable.count(elemSynName) != 1) { //single syn, count can only be 1
                        return false;
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }

	return true;
}
