#include "PQLOneSynonymCheck.h"

PQLOneSynonymCheck::PQLOneSynonymCheck() {

}

PQLOneSynonymCheck::~PQLOneSynonymCheck() {

}

std::string PQLOneSynonymCheck::getPrimitiveType(std::string varName) { return ""; }

bool PQLOneSynonymCheck::checkPQLOneSynonym(Query query) {
	std::multimap<std::string, std::string> varTable = query.getVarTable();
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
	if (varTable.count(selectClause.getVarName()) != 1) {
		return false;
	}

    // to do check whether integer or underscore(non synonym)
    // SuchThat Clause
    for (SuchThatClause suchThatClause: suchThatClauseVec) {
        std::string suchThatLeftType = getPrimitiveType(suchThatClause.getLeftArg());
        std::string suchThatRightType = getPrimitiveType(suchThatClause.getRightArg());
        if (checkSynonym() && varTable.count(suchThatLeftType) != 1) {
            return false;
        }

        if (checkSynonym() && varTable.count(suchThatRightType) != 1) {
            return false;
        }

    }

    // Pattern Clause
    for (PatternClause patternClause: patternClauseVec) {
    	std::string patternLeftType = getPrimitiveType(patternClause.getLeftArg());
    	std::string patternRightType = getPrimitiveType(patternClause.getRightArg());
        if (checkSynonym() && varTable.count(patternLeftType) != 1) {
            return false;
        }

        if (checkSynonym() && varTable.count(patternRightType) != 1) {
            return false;
        }
        // Further Check: syn - assign must be declared as a synonym of an assignment(design entity assign)
        if (checkSynonym() && varTable.find(patternRightType)->second != "assign") {
            return false;
        }
    }


	return true;
}

bool PQLOneSynonymCheck::checkSynonym() {
	return false;
}