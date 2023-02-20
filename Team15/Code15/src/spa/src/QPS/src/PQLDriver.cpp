
#include "QPS/include/PQLDriver.h"

PQLDriver::PQLDriver(PKB& pkb) : evaluator(pkb) {
    this->pkb = pkb;
    this->preprocessor = PQLPreprocessor();
}

std::set<std::string> PQLDriver::processPQL(std::string queryStr) {
    std::set<std::string> results;
    try {
        // Call preprocessor
        Query query = preprocessor.preprocess(queryStr);

        // Call evaluator
        results = evaluator.evaluate(query);

        // return results
        return results;

    } catch(PQLSyntaxError syntaxError) {
        results.insert("SyntaxError");
        return results;
    } catch(PQLSemanticError semanticError) {
        results.insert("SemanticError");
        return results;
    }

}