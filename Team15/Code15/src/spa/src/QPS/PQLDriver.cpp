
#include "PQLDriver.h"

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
        // Write something in results
        return results;
    } catch(PQLSemanticError semanticError) {
        // Write something in results
        return results;
    }

}