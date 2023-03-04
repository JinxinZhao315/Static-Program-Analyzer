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

    std::string firstArgName;
    /*std::unordered_map<std::string, SynonymLinkageMap> firstArgValue;*/
    bool isFirstArgAvailable;


    std::string secondArgName;
    //std::unordered_map<std::string, SynonymLinkageMap> secondArgValue;
    bool isSecondArgAvailable;

    ResultTable clauseResult;
public:
    Result(): isTrue(true),
              isFirstArgAvailable(false), isSecondArgAvailable(false){}
    Result(bool isTrue, std::string firstArgName, ResultTable tempResult) :
            isTrue(true), firstArgName(firstArgName), clauseResult(tempResult), 
            isFirstArgAvailable(true), isSecondArgAvailable(false) {}
    Result(bool isTrue,
           std::string firstArgName, std::string secondArgName, ResultTable tempResult) :
            isTrue(true), firstArgName(firstArgName), isFirstArgAvailable(true),
            secondArgName(secondArgName), isSecondArgAvailable(true), clauseResult(tempResult) {}

    bool isResultTrue();
    void setResultTrue(bool isTrueValue);

    std::string getFirstArgName();
    /*void setFirstArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value);*/
    bool isFirstArgSynonym();

    std::string getSecondArgName();
    /*void setSecondArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value);*/
    bool isSecondArgSynonym();
    
    void setClauseResult(bool isFirstArgAvailable, bool isSecondArgAvailable, ResultTable tempResult);

    ResultTable getClauseResult();
};


#endif //SPA_RESULT_H
