#include"PQLPreprocessor.h"

PQLPreprocessor::PQLPreprocessor() {};

Query PQLPreprocessor::preprocess(std::string input) {
	QueryTokenizer tokenizer;
	Query query;
	std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
	std::multimap<std::string, std::string> varTable;
	varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
	query.addVarTable(varTable);
	SelectClause selectClause;
	SuchThatClause suchThatClause;
	PatternClause patternClause;
	tokenizer.tokenizeClauses(declarationClausePair.second, selectClause, suchThatClause, patternClause);
	query.addSelectClause(selectClause);
	query.addSuchThatClause(suchThatClause);
	query.addPatternClause(patternClause);

	return query;
}