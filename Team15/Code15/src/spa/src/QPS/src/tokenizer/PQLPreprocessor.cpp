#include"QPS/include/tokenizer/PQLPreprocessor.h"

PQLPreprocessor::PQLPreprocessor() {
    this->tokenizer = QueryTokenizer();
    this->semanticChecker = PQLSemanticCheck();
};

Query PQLPreprocessor::preprocess(std::string input) {
    Query query = Query();
    std::multimap<std::string, std::string> varTable;
    SelectClause selectClause;

    std::vector<SuchThatClause> suchThatClauseVec;
    std::vector<PatternClause> patternClauseVec;
    std::vector<WithClause> withClauseVec;

    // Tokenize & syntax check
	std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
	varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
    query.setSynonymTable(varTable);
	tokenizer.tokenizeClauses(declarationClausePair.second, varTable, selectClause, suchThatClauseVec, patternClauseVec, withClauseVec);
    query.setSelectClause(selectClause);
    query.setSuchThatClauseVec(suchThatClauseVec);
    query.setPatternClauseVec(patternClauseVec);
    query.setWithClauseVec(withClauseVec);

    // semantic check
    std::pair<bool,std::string> semanticCheckPair = semanticChecker.checkSemantics(query);
    bool isSemanticValid = semanticCheckPair.first;
    if (!isSemanticValid) {
        throw PQLSemanticError(semanticCheckPair.second);
    }
	return query;
}