#pragma once

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity
{
private:
    EntityManager &manager;
    bool active;
    std::vector<Component *> components;

public:
    std::string name;

    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool Active() const;

    template <typename T, typename... TArgs>
    T &AddComponent(TArgs &&... args)
    {
        T *newComponent = new T(std::forward<TArgs>(args)...);
        newComponent->owner = this;
        this->entities.emplace_back(newComponent);
        newComponent->Init();

        return *newComponent;
    }
};