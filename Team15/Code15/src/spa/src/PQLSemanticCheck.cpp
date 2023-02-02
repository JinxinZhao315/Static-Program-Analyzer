#include "PQLSemanticCheck.h"

PQLSemanticCheck::PQLSemanticCheck() {}

PQLSemanticCheck::~PQLSemanticCheck() {}

bool PQLSemanticCheck::checkSynonym() { return false; }

std::pair<bool,std::string> PQLSemanticCheck::checkSemantics(Query query) {
	/*A synonym name can only be declared once.
		All the synonyms used in clauses must be declared exactly once.
		syn - assign must be declared as a synonym of an assignment(design entity assign).
		The first argument for Modifies and Uses cannot be _, as it is unclear whether _ refers to a statement or procedure.
		Synonyms of design entities can appear as relationship arguments, and should match the design entity defined for the relationship.
		E.g.For Parent(arg1, arg2), if arg1 is a synonym, then arg1 must be a statement synonym, or a subtype of a statement synonym(read, print, assign, if, while, call).
		E.g.For Modifies(arg1, arg2), if arg2 is a synonym, then arg2 must be a variable synonym.*/
	std::shared_ptr<PQLOneSynonymCheck> oneSynonymCheckInstance = std::make_shared<PQLOneSynonymCheck>();
	std::shared_ptr<PQLRefConsistentCheck> refConsistentCheckInstance = std::make_shared<PQLRefConsistentCheck>();


	if (!oneSynonymCheckInstance->checkPQLOneSynonym(query)) {
		return std::make_pair(false, "PQL semantic error: synonym declared more than once");
	};
	if (!refConsistentCheckInstance->checkPQLRefConsistent(query)) {
		return std::make_pair(false, "PQL semantic error: inconsistent reference");
	};
	return std::make_pair(true, "");
}