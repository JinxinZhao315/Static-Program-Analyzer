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

    std::string leftArgName;
    std::set<std::string> leftArgValue;
    bool isLeftArgAvailable;


    std::string rightArgName;
    std::set<std::string> rightArgValue;
    bool isRightArgAvailable;
public:
    Result(): isTrue(true),
        isLeftArgAvailable(false), isRightArgAvailable(false){}
    Result(bool isTrue, std::string leftArgName, std::set<std::string> leftArgValue) :
        isTrue(true), leftArgName(leftArgName), leftArgValue(leftArgValue), isLeftArgAvailable(true) {}
    Result(bool isTrue, 
        std::string leftArgName, std::set<std::string> leftArgValue,
        std::string rightArgName, std::set<std::string> rightArgValue) :
        isTrue(true), leftArgName(leftArgName), leftArgValue(leftArgValue), isLeftArgAvailable(true),
        rightArgName(rightArgName), rightArgValue(rightArgValue), isRightArgAvailable(true) {}

    bool isResultTrue();
    void setResultTrue(bool isTrueValue);

    std::string getLeftArgName();
    std::set<std::string> getLeftArgValue();
    void setLeftArg(std::string name, std::set<std::string> value);
    bool isLeftArgSynonym();

    std::string getRightArgName();
    std::set<std::string> getRightArgValue();
    void setRightArg(std::string name, std::set<std::string> value);
    bool isRightArgSynonym();
};


#endif //SPA_RESULT_H
