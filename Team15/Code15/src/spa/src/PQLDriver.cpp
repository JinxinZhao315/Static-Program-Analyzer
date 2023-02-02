
#include "PQLDriver.h"

PQLDriver::PQLDriver() {
    this->preprocessor = PQLPreprocessor();
    this->evaluator = PQLEvaluator();
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