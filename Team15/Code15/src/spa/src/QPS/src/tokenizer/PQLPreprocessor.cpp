#include"QPS/include/tokenizer/PQLPreprocessor.h"

PQLPreprocessor::PQLPreprocessor() {
    this->tokenizer = QueryTokenizer();
    this->semanticChecker = PQLSemanticCheck();
};

Query PQLPreprocessor::preprocess(std::string input) {
    
    std::multimap<std::string, std::string> varTable;
    std::vector<SuchThatClause*> suchThatClauseVec;
    std::vector<PatternClause*> patternClauseVec;
    std::vector<WithClause*> withClauseVec;
    SelectClause* selectClause = new SelectClause();

    // Tokenize & syntax check
	std::pair<std::string, std::string> declarationClausePair = tokenizer.tokenizeQuery(input);
	varTable = tokenizer.tokenizeDeclaration(declarationClausePair.first);
	tokenizer.tokenizeClauses(declarationClausePair.second, varTable, selectClause, suchThatClauseVec, patternClauseVec, withClauseVec);

    Query query = *new Query();
    query.setSynonymTable(varTable);
    query.addAllSuchThatClauses(suchThatClauseVec);
    query.addAllPatternClauses(patternClauseVec);
    query.addAllWithClauses(withClauseVec);
    query.addSelectClause(selectClause);

    // semantic check
    std::pair<bool,std::string> semanticCheckPair = semanticChecker.checkSemantics(query);
    bool isSemanticValid = semanticCheckPair.first;
    if (!isSemanticValid) {
        throw PQLSemanticError(semanticCheckPair.second);
    }

    //reorder evaluation sequence
    QueryEvalSeqOptimizer optimizer;
    optimizer.optimizeEvalSeq(query);
	return query;
}