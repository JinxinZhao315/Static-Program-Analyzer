#include "qps/include/model/Query.h"
#include "qps/include/tokenizer/PQLPreprocessor.h"
#include "qps/include/evaluator/PQLEvaluator.h"
#include "pkb/include/PKB.h"
#include "exceptions/PQLSyntaxError.h"
#include "exceptions/PQLSemanticError.h"
#include <string>
#ifndef SPA_PQLDRIVER_H
#define SPA_PQLDRIVER_H


class PQLDriver {
public:
    PQLDriver(PKB& pkb);
    std::set<std::string> processPQL(std::string queryStr);
private:
    PQLPreprocessor preprocessor;
    PQLEvaluator evaluator;
    PKB pkb;
};


#endif //SPA_PQLDRIVER_H
