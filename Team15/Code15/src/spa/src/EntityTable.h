#pragma once

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename Id, typename E>
class EntityTable {
public:
    virtual void storeEntity(E *entity) {
        idList.insert(entity->getId());
        entityList[entity->getId()] = entity;
    }

    virtual vector<Id> getIdList() {
        return vector<Id>(idList.begin(), idList.end());
    }

    virtual E* retrieveEntity(const Id& id) {
        auto pair = entityList.find(id);
        if (pair == entityList.end()) {
            return nullptr;
        }
        return pair->second;
    }

private:
    std::unordered_set<Id> idList;
    std::unordered_map<Id, E*> entityList;
};