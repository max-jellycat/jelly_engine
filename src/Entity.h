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
    EntityManager &m_manager;
    bool m_isActive;
    std::vector<Component *> m_components;
    std::map<const std::type_info *, Component *> m_componentTypeMap;

public:
    std::string name;

    explicit Entity(EntityManager &manager);

    Entity(EntityManager &manager, std::string name);

    void Update(float deltaTime);

    void Render();

    void Destroy();

    void ListComponents() const;

    bool IsActive() const;

    template<typename T, typename... TArgs>
    T &AddComponent(TArgs &&... args) {
        T *newComponent = new T(std::forward<TArgs>(args)...);
        newComponent->owner = this;
        m_components.emplace_back(newComponent);
        m_componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Init();

        return *newComponent;
    }

    template<typename T>
    T *GetComponent() {
        return static_cast<T *>(m_componentTypeMap[&typeid(T)]);
    }
};