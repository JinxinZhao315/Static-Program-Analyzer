#include "TokenMap.h"

TokenMap::TokenMap() {}

std::string TokenMap::getStringByToken(Tokens::Keyword keyword) {
    if(stringExistsByToken(keyword)) {
        return this->doubleKeyedTokenMap.first.at(keyword);
    }
}

bool TokenMap::stringExistsByToken(Tokens::Keyword keyword) {
    return this->doubleKeyedTokenMap.first.count(keyword);
}

bool TokenMap::tokenExistsByString(std::string token) {
    return this->doubleKeyedTokenMap.second.count(token);
}

Tokens::Keyword TokenMap::getTokenByString(std::string token) {
    if(tokenExistsByString(token)) {
        return this->doubleKeyedTokenMap.second[token];
    }
}
