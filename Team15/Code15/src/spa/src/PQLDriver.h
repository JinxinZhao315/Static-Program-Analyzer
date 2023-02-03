#include "Query.h"
#include "PQLPreprocessor.h"
#include "PQLEvaluator.h"
#include "PKB.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"
#include <string>
#ifndef SPA_PQLDRIVER_H
#define SPA_PQLDRIVER_H


class PQLDriver {
public:
    PQLDriver(PKB pkb);
    std::string processPQL(std::string queryStr);
private:
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator;
    PKB pkb;
};


#endif //SPA_PQLDRIVER_H
