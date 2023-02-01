#include "PQLOneSynonymCheck.h"

PQLOneSynonymCheck::PQLOneSynonymCheck() {

}

PQLOneSynonymCheck::~PQLOneSynonymCheck() {

}

bool PQLOneSynonymCheck::checkPQLOneSynonym(PreProcessedResults preProcessedResults) {
	std::multimap<std::string, std::string> varTable = preProcessedResults.getVarTable();
	SelectClause selectClause = preProcessedResults.getSelectClause();
	PatternClause patternClause = preProcessedResults.getPatternClause();
	SuchThatClause suchThatClause = preProcessedResults.getSuchThatClause();

	// to do check whether integer or underscore(non synonym)
	std::string suchThatLeftType = suchThatClause.getLeftPair().first;
	std::string suchThatRightType = suchThatClause.getRightPair().first;
	std::string patternLeftType = patternClause.getLeftPair().first;
	std::string patternRightType = patternClause.getRightPair().first;

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
	if (varTable.count(selectClause.getVarEntityPair().first) != 1) {
		return false;
	}

	// SuchThat Clause
	if (checkSynonym() && varTable.count(suchThatLeftType) != 1) {
		return false;
	}

	if (checkSynonym() && varTable.count(suchThatRightType) != 1) {
		return false;
	}

	// Pattern Clause
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
	return true;
}

bool PQLOneSynonymCheck::checkSynonym() {
	return false;
}