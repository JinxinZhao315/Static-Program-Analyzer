#pragma once

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename Id, typename E>
class EntityTable {
public:
    virtual void addEntity(E* entity) {
        ids.insert(entity->getId());
        entities[entity->getId()] = entity;
    }

    virtual vector<Id> getids() {
        return vector<Id>(ids.begin(), ids.end());
    }

    virtual E* getEntity(const Id& id) {
        auto pair = entities.find(id);
        if (pair == entities.end()) {
            return nullptr;
        }
        return pair->second;
    }

private:
    unordered_set<Id> ids;
    unordered_map<Id, E*> entities;
};