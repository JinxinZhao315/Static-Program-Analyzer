#include "Query.h"
#include "PQLPreprocessor.h"
#include "PQLEvaluator.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"
#include <string>
#ifndef SPA_PQLDRIVER_H
#define SPA_PQLDRIVER_H


class PQLDriver {
public:
    PQLDriver();
    std::string processPQL(std::string queryStr);
private:
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator;
};


#endif //SPA_PQLDRIVER_H
