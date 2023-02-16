
#include "QPS/include/PQLDriver.h"

PQLDriver::PQLDriver(PKB& pkb) : evaluator(pkb) {
    this->pkb = pkb;
    this->preprocessor = PQLPreprocessor();
}

std::string PQLDriver::processPQL(std::string queryStr) {
    std::string results;
    try {
        // Call preprocessor
        Query query = preprocessor.preprocess(queryStr);

        // Call evaluator
        results = evaluator.evaluate(query);

        // return results
        return results;

    } catch(PQLSyntaxError syntaxError) {
        results = "SyntaxError";
        return results;
    } catch(PQLSemanticError semanticError) {
        results  = "SemanticError";
        return results;
    }

}