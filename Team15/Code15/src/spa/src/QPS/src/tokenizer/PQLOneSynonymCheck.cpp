#include "QPS/include/tokenizer/PQLOneSynonymCheck.h"

PQLOneSynonymCheck::PQLOneSynonymCheck() {

}

PQLOneSynonymCheck::~PQLOneSynonymCheck() {

}

bool PQLOneSynonymCheck::checkPQLOneSynonym(Query query) {
	std::multimap<std::string, std::string> varTable = query.getSynonymTable();
	SelectClause selectClause = query.getSelectClause();
    std::vector<PatternClause> patternClauseVec = query.getPatternClauseVec();
	std::vector<SuchThatClause> suchThatClauseVec = query.getSuchThatClauseVec();
    std::vector<WithClause> withClauseVec = query.getWithClauseVec();


	//PQLConstants::RelRefType suchThatType = suchThatClause->relRefType;
	// A synonym name can only be declared once.
	for (auto iter = varTable.begin(); iter != varTable.end(); iter++) {
		// Only can be greater than 1.
		if (varTable.count(iter->first) != 1) {
			return false;
		}
	}
	// All the synonyms used in clauses must be declared exactly once.

	// Select Clause
	// toDo remove type attribute in selectClause
	// Check if haven't been defined after checking all synonyms declared once.
    std::vector<Elem> elemVec = selectClause.getSynNameVec();
    //if (synNameVec.size() > 1) {
    //    for (std::string synName : synNameVec) {
    //        if (varTable.count(synName) != 1) {//multiple synonyms, can't be BOOLEAN
    //            return false;
    //        }
    //    }
    //}
    //else {//size == 1
    //    if (synNameVec[0] == "BOOLEAN" && varTable.count(synNameVec[0]) > 1) {//if single syn and BOOLEAN, count can be 0 or 1
    //        return false;
    //    }
    //    else if (synNameVec[0] != "BOOLEAN" && varTable.count(synNameVec[0]) != 1) {//single syn, count can only be 1
    //        return false;
    //    }
    //}
    for (Elem elem : elemVec) {
        if (elemVec.size() > 1) {
            if (varTable.count(elem.getSynName()) != 1) {//multiple synonyms, can't be BOOLEAN
                return false;
            }
        }
        else {//synNameVec.size == 1
            if (elem.getSynName() == "BOOLEAN" && varTable.count(elem.getSynName()) > 1) {//if single syn and BOOLEAN, count can be 0 or 1
                return false;
            }
            else if (elem.getSynName() != "BOOLEAN" && varTable.count(elem.getSynName()) != 1) {//single syn, count can only be 1
                return false;
            }
        }
    }

    // to do check whether integer or underscore(non synonym)
    // SuchThat Clause
    for (SuchThatClause suchThatClause: suchThatClauseVec) {
        std::string suchThatLeftArg = suchThatClause.getLeftArg();
        std::string suchThatRightArg = suchThatClause.getRightArg();
        std::string suchThatLeftType = Utility::getReferenceType(suchThatLeftArg);
        std::string suchThatRightType = Utility::getReferenceType(suchThatRightArg);
        if (suchThatLeftType == Utility::SYNONYM && varTable.count(suchThatLeftArg) != 1) {
            return false;
        }

        if (suchThatRightType == Utility::SYNONYM && varTable.count(suchThatRightArg) != 1) {
            return false;
        }

    }

    // Pattern Clause
    for (PatternClause patternClause: patternClauseVec) {
        // In a pattern clause, only the pattern synonym and the first argument can be synonyms
        std::string patternSynonym = patternClause.getPatternSynonym();
        std::string patternFirstArg = patternClause.getFirstArg();
        std::string patternSynonymType = Utility::getReferenceType(patternSynonym);
    	std::string patternFirstType = Utility::getReferenceType(patternFirstArg);

        if (patternSynonymType == Utility::SYNONYM && varTable.count(patternSynonym) != 1) {
            return false;
        }

        if (patternFirstType == Utility::SYNONYM && varTable.count(patternFirstArg) != 1) {
            return false;
        }

        // Further Check: syn - assign must be declared as a synonym of an assignment(design entity assign)
//        if (patternSecondType == Utility::SYNONYM && varTable.find(patternSecondArg)->second != "assign") {
//            return false;
//        }
    }

    //attrRef synName should be in varTable
    for (WithClause withClause : withClauseVec) {
        if (withClause.getFirstArg().isRefAttrRef()) {
            std::string firstArg = withClause.getFirstArg().getAttrRef().getSynName();
            if (varTable.count(firstArg) != 1) {
                return false;
            }
        }
        if (withClause.getSecondArg().isRefAttrRef()) {
            std::string secondArg = withClause.getSecondArg().getAttrRef().getSynName();
            if (varTable.count(secondArg) != 1) {
                return false;
            }
        }
    }


	return true;
}
