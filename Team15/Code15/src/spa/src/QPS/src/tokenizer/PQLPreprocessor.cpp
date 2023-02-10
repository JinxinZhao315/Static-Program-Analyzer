#include"QPS/include/tokenizer/PQLPreprocessor.h"

PQLPreprocessor::PQLPreprocessor() {
    this->tokenizer = QueryTokenizer();
    this->semanticChecker = PQLSemanticCheck();
};

Query PQLPreprocessor::preprocess(std::string input) {
    Query query = Query();
    std::multimap<std::string, std::string> varTable;
    SelectClause selectClause;
    SuchThatClause suchThatClause;
    PatternClause patternClause;

    // TODO: Set these vectors in tokenizer.tokenizeClauses.
    std::vector<SelectClause> selectClauseVec;
    std::vector<SuchThatClause> suchThatClauseVec;
    std::vector<PatternClause> patternClauseVec;

    // Tokenize & syntax check
	std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
	varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
    query.addSynonymTable(varTable);
	tokenizer.tokenizeClauses(declarationClausePair.second, selectClause, suchThatClause, patternClause);
	query.addSelectClause(selectClause);
    if (!suchThatClause.getRelationShip().empty()) {
        // TODO: In query object, change addSuchThatClause method to setSuchThatClauseVector
        // TODO: where you directly use the vectors declared above to set the sucThatClauseVector attribute of query class
        query.addSuchThatClause(suchThatClause);
    }
    if (!patternClause.getPatternSynonym().empty()) {
        query.addPatternClause(patternClause);
    }

    // semantic check
    std::pair<bool,std::string> semanticCheckPair = semanticChecker.checkSemantics(query);
    bool isSemanticValid = semanticCheckPair.first;
    if (!isSemanticValid) {
        throw PQLSemanticError(semanticCheckPair.second);
    }

	return query;
}