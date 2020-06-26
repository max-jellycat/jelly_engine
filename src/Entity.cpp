#include <iostream>
#include <utility>
#include "Entity.h"

Entity::Entity(EntityManager &manager)
        : m_manager(manager) {
    m_isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name)
        : m_manager(manager), name(std::move(name)) {
    m_isActive = true;
}

void Entity::Update(float deltaTime) {
    for (auto &component : m_components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto &component : m_components) {
        component->Render();
    }
}

void Entity::Destroy() {
    m_isActive = false;
}

void Entity::ListComponents() const {
    for (auto &component: m_componentTypeMap) {
        std::cout << "  Component<" << component.first->name() << ">" << std::endl;
    }
}

bool Entity::IsActive() const { return m_isActive; }