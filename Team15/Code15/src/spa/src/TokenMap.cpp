#include "TokenMap.h"

TokenMap::TokenMap() {}

std::string TokenMap::getStringByToken(Tokens::Keyword keyword) {
    return this->doubleKeyedTokenMap.first.at(keyword);
}

Tokens::Keyword TokenMap::getTokenByString(std::string token) {
    return this->doubleKeyedTokenMap.second.at(token);
}

bool TokenMap::findToken(std::string s) {
    if(getTokenByString(s)) {
        return true;
    } else {
        return false;
    }
}
