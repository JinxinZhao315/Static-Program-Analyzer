#include"PQLPreprocessor.h"

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

    // Tokenize & syntax check
	std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
	varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
	query.addVarTable(varTable);
	tokenizer.tokenizeClauses(declarationClausePair.second, selectClause, suchThatClause, patternClause);
	query.addSelectClause(selectClause);
	query.addSuchThatClause(suchThatClause);
	query.addPatternClause(patternClause);

    // semantic check
    std::pair<bool,std::string> semanticCheckPair = semanticChecker.checkSemantics(query);
    bool isSemanticValid = semanticCheckPair.first;
    if (!isSemanticValid) {
        throw PQLSemanticError(semanticCheckPair.second);
    }

	return query;
}