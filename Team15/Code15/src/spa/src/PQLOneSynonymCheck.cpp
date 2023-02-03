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
        std::string suchThatLeftArg = suchThatClause.getLeftArg();
        std::string suchThatRightArg = suchThatClause.getRightArg();
        std::string suchThatLeftType = getPrimitiveType(suchThatLeftArg);
        std::string suchThatRightType = getPrimitiveType(suchThatRightArg);
        if (suchThatLeftType == "synonym" && varTable.count(suchThatLeftArg) != 1) {
            return false;
        }

        if (suchThatRightType == "synonym" && varTable.count(suchThatRightArg) != 1) {
            return false;
        }

    }

    // Pattern Clause
    for (PatternClause patternClause: patternClauseVec) {
        std::string patternLeftArg = patternClause.getLeftArg();
        std::string patternRightArg = patternClause.getRightArg();
    	std::string patternLeftType = getPrimitiveType(patternClause.getLeftArg());
    	std::string patternRightType = getPrimitiveType(patternClause.getRightArg());
        if (patternLeftType == "synonym" && varTable.count(patternLeftArg) != 1) {
            return false;
        }

        if (patternRightType == "synonym" && varTable.count(patternRightArg) != 1) {
            return false;
        }
        // Further Check: syn - assign must be declared as a synonym of an assignment(design entity assign)
        if (patternRightType == "synonym" && varTable.find(patternRightArg)->second != "assign") {
            return false;
        }
    }


	return true;
}

bool PQLOneSynonymCheck::checkSynonym() {
	return false;
}