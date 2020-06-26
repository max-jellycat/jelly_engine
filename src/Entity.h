#pragma once

#include <vector>
#include <map>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;

class EntityManager;

class Entity {
private:
    EntityManager &manager;
    bool active;
    std::vector<Component *> components;
    std::map<const std::type_info *, Component *> componentTypeMap;

public:
    std::string name;

    explicit Entity(EntityManager &manager);

    Entity(EntityManager &manager, std::string name);

    void Update(float deltaTime);

    void Render();

    void Destroy();

    bool Active() const;

    template<typename T, typename... TArgs>
    T &AddComponent(TArgs &&... args) {
        T *newComponent = new T(std::forward<TArgs>(args)...);
        newComponent->owner = this;
        this->components.emplace_back(newComponent);
        this->componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Init();

        return *newComponent;
    }

    template<typename T>
    T *GetComponent() {
        return static_cast<T *>(componentTypeMap[&typeid(T)]);
    }
};