//
// Created by Jinxin Zhao on 3/2/23.
//
#include<set>
#include<string>
#include "SynonymLinkageMap.h"
#include "ResultTable.h"

#ifndef SPA_RESULT_H
#define SPA_RESULT_H


class Result {
private:
    bool isTrue;

    ResultTable clauseResult;
public:
    Result(): isTrue(true){}
    Result(bool isTrue,ResultTable tempResult) :
            isTrue(true), clauseResult(tempResult) {}

    bool isResultTrue();

    void setResultTrue(bool isTrueValue);
    
    void setClauseResult(ResultTable tempResult);

    ResultTable getClauseResult();
};


#endif //SPA_RESULT_H
