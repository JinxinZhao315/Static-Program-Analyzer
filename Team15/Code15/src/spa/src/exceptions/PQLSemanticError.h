//
// Created by Jinxin Zhao on 1/2/23.
//

#ifndef SPA_PQLSEMANTICERROR_H
#define SPA_PQLSEMANTICERROR_H

#include <iostream>
#include <string>

class PQLSemanticError : public std::exception {
private:
    std::string message;

public:
    PQLSemanticError(std::string msg) : message(msg) {}
    std::string what() {
        return message;
    }
};


#endif //SPA_PQLSEMANTICERROR_H
