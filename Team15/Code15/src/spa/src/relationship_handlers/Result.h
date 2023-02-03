//
// Created by Jinxin Zhao on 3/2/23.
//

#ifndef SPA_RESULT_H
#define SPA_RESULT_H


class Result {
private:
    bool isTrue;
public:
    Result(): isTrue(true) {}
    bool isResultTrue();
    void setResultTrue(bool isTrueValue);
};


#endif //SPA_RESULT_H
