#pragma once

#include <vector>
#include "Entity.h"
#include "Component.h"

class EntityManager {
private:
    std::vector<Entity *> m_entities;

public:
    void ClearData();

    void Update(float deltaTime);

    void Render();

    Entity &AddEntity(std::string name);

    std::vector<Entity *> GetEntities() const;

    void ListEntities() const;

    bool HasNoEntities() const;

    unsigned int GetEntityCount() const;
};