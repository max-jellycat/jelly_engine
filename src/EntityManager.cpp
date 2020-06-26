#include "EntityManager.h"

#include <utility>
#include <iostream>

void EntityManager::ClearData() {
    for (auto &entity : this->entities) {
        entity->Destroy();
    }
}

void EntityManager::PrintEntities() const {
    for(auto& entity: this->entities) {
        std::cout << "Entity: " << entity->name << std::endl;
        entity->PrintComponents();
    }
}

bool EntityManager::HasNoEntities() const { return this->entities.empty(); }

void EntityManager::Update(float deltaTime) {
    for (auto &entity : this->entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (auto &entity : this->entities) {
        entity->Render();
    }
}

Entity &EntityManager::AddEntity(std::string name) {
    auto *entity = new Entity(*this, std::move(name));
    this->entities.emplace_back(entity);

    return *entity;
}

std::vector<Entity *> EntityManager::GetEntities() const { return this->entities; }

unsigned int EntityManager::GetEntityCount() const { return this->entities.size(); }
