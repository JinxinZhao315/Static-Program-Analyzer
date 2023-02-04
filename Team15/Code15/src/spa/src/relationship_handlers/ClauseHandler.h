//
// Created by Jinxin Zhao on 3/2/23.
//
#include "PKB.h"
#include "ResultTable.h"

#ifndef SPA_CLAUSEHANDLER_H
#define SPA_CLAUSEHANDLER_H


class ClauseHandler {
public:
    ClauseHandler(PKB& pkb);
protected:
    void combineResult(ResultTable& resultTable, Result& result);
private:
    PKB pkb;
};


#endif //SPA_CLAUSEHANDLER_H
