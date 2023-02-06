#include "TokenMap.h"

TokenMap::TokenMap() {}

std::string TokenMap::getStringByToken(Tokens::Keyword keyword) {
    if(stringExistsByToken(keyword)) {
        return this->doubleKeyedTokenMap.first.at(keyword);
    }
}

bool TokenMap::stringExistsByToken(Tokens::Keyword keyword) {
    try {
        this->doubleKeyedTokenMap.first.at(keyword);
        return true;
    } catch (std::exception exception){
        return false;
    }
}

bool TokenMap::tokenExistsByString(std::string token) {
    try {
        this->doubleKeyedTokenMap.second.at(token);
        return true;
    } catch (std::exception exception){
        return false;
    }
}

Tokens::Keyword TokenMap::getTokenByString(std::string token) {
    if(tokenExistsByString(token)) {
        return this->doubleKeyedTokenMap.second.at(token);
    }
}
