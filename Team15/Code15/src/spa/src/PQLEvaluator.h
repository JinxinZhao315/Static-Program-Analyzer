//
// Created by Jinxin Zhao on 2/2/23.
//
#include "Query.h"
#include <string>
#ifndef SPA_PQLEVALUATOR_H
#define SPA_PQLEVALUATOR_H


class PQLEvaluator {
public:
    PQLEvaluator();
    std::string evaluate(Query query);

};


#endif //SPA_PQLEVALUATOR_H
