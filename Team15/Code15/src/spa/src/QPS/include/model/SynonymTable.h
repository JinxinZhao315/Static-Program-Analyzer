#include <map>
#include <string>
#ifndef SPA_SYNONYMTABLE_H
#define SPA_SYNONYMTABLE_H


class SynonymTable {
private:
    std::multimap<std::string, std::string> synonTable;

public:
    SynonymTable();
    void addSynonTypePair(std:: string synonName, std::string type);
    std::string getTypeFromSynon(std::string type);

};


#endif //SPA_SYNONYMTABLE_H
