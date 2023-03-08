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
    for (std::string synName : selectClause.getSynNameVec()) {
        if (varTable.count(synName) != 1) {
            return false;
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


	return true;
}
