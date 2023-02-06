#include <map>
#include <string>
#include <utility>
#include "Tokens.h"

class TokenMap {
private:
    std::pair<std::map<Tokens::Keyword, std::string>, std::map<std::string, Tokens::Keyword>> doubleKeyedTokenMap;
public:
    TokenMap();

    Tokens::Keyword getTokenByString(std::string token);

    std::string getStringByToken(Tokens::Keyword keyword);

    void setMap(std::map<Tokens::Keyword, std::string> mapToString, std::map<std::string, Tokens::Keyword> mapToKeywords);

    bool findToken(std::string s);
};