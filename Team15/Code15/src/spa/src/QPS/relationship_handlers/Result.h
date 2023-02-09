//
// Created by Jinxin Zhao on 3/2/23.
//
#include<set>
#include<string>

#ifndef SPA_RESULT_H
#define SPA_RESULT_H


class Result {
private:
    bool isTrue;

    std::string firstArgName;
    std::set<std::string> firstArgValue;
    bool isfirstArgAvailable;


    std::string secondArgName;
    std::set<std::string> secondArgValue;
    bool isSecondArgAvailable;
public:
    Result(): isTrue(true),
              isfirstArgAvailable(false), isSecondArgAvailable(false){}
    Result(bool isTrue, std::string firstArgName, std::set<std::string> firstArgValue) :
            isTrue(true), firstArgName(firstArgName), firstArgValue(firstArgValue), isfirstArgAvailable(true) {}
    Result(bool isTrue,
           std::string firstArgName, std::set<std::string> firstArgValue,
           std::string secondArgName, std::set<std::string> secondArgValue) :
            isTrue(true), firstArgName(firstArgName), firstArgValue(firstArgValue), isfirstArgAvailable(true),
            secondArgName(secondArgName), secondArgValue(secondArgValue), isSecondArgAvailable(true) {}

    bool isResultTrue();
    void setResultTrue(bool isTrueValue);

    std::string getFirstArgName();
    std::set<std::string> getFirstArgValue();
    void setFirstArg(std::string name, std::set<std::string> value);
    bool isFirstArgSynonym();

    std::string getSecondArgName();
    std::set<std::string> getSecondArgValue();
    void setSecondArg(std::string name, std::set<std::string> value);
    bool isSecondArgSynonym();
};


#endif //SPA_RESULT_H
