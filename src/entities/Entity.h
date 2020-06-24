#pragma once
#include <vector>
#include <string>
#include "../EntityManager.h"
#include "../components/Component.h"

class Entity
{
private:
    std::string m_name;
    EntityManager &m_manager;
    bool m_active;
    std::vector<Component *> m_components;

public:
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    void GetName() const;
    bool Active() const;
};