#include "EntityManager.h"

#include <utility>
#include <iostream>

void EntityManager::ClearData() {
    for (auto &entity : m_entities) {
        entity->Destroy();
    }
}

void EntityManager::ListEntities() const {
    unsigned int i = 0;
    for(auto& entity: m_entities) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->ListComponents();
        i++;
    }
}

bool EntityManager::HasNoEntities() const { return m_entities.empty(); }

void EntityManager::Update(float deltaTime) {
    for (auto &entity : m_entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (auto &entity : m_entities) {
        entity->Render();
    }
}

Entity &EntityManager::AddEntity(std::string name) {
    auto *entity = new Entity(*this, std::move(name));
    m_entities.emplace_back(entity);

    return *entity;
}

std::vector<Entity *> EntityManager::GetEntities() const { return m_entities; }

unsigned int EntityManager::GetEntityCount() const { return m_entities.size(); }
