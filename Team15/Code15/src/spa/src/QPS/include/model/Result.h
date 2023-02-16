//
// Created by Jinxin Zhao on 3/2/23.
//
#include<set>
#include<string>
#include "SynonymLinkageMap.h"

#ifndef SPA_RESULT_H
#define SPA_RESULT_H


class Result {
private:
    bool isTrue;

    std::string firstArgName;
    std::unordered_map<std::string, SynonymLinkageMap> firstArgValue;
    bool isFirstArgAvailable;


    std::string secondArgName;
    std::unordered_map<std::string, SynonymLinkageMap> secondArgValue;
    bool isSecondArgAvailable;
public:
    Result(): isTrue(true),
              isFirstArgAvailable(false), isSecondArgAvailable(false){}
    Result(bool isTrue, std::string firstArgName, std::unordered_map<std::string, SynonymLinkageMap> firstArgValue) :
            isTrue(true), firstArgName(firstArgName), firstArgValue(firstArgValue), 
            isFirstArgAvailable(true), isSecondArgAvailable(false) {}
    Result(bool isTrue,
           std::string firstArgName, std::unordered_map<std::string, SynonymLinkageMap> firstArgValue,
           std::string secondArgName, std::unordered_map<std::string, SynonymLinkageMap> secondArgValue) :
            isTrue(true), firstArgName(firstArgName), firstArgValue(firstArgValue), isFirstArgAvailable(true),
            secondArgName(secondArgName), secondArgValue(secondArgValue), isSecondArgAvailable(true) {}

    bool isResultTrue();
    void setResultTrue(bool isTrueValue);

    std::string getFirstArgName();
    std::unordered_map<std::string, SynonymLinkageMap> getFirstArgValue();
    void setFirstArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value);
    bool isFirstArgSynonym();

    std::string getSecondArgName();
    std::unordered_map<std::string, SynonymLinkageMap> getSecondArgValue();
    void setSecondArg(std::string name, std::unordered_map<std::string, SynonymLinkageMap> value);
    bool isSecondArgSynonym();
};


#endif //SPA_RESULT_H
