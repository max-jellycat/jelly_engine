#include "EntityManager.h"

void EntityManager::ClearData()
{
    for (auto &entity : this->entities)
    {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() const { return this->entities.size() == 0; }

void EntityManager::Update(float deltaTime)
{
    for (auto &entity : this->entities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for (auto &entity : this->entities)
    {
        entity->Render();
    }
}

Entity &EntityManager::AddEntity(std::string name)
{
    Entity *entity = new Entity(*this, name);
    this->entities.emplace_back(entity);

    return *entity;
}

std::vector<Entity *> EntityManager::GetEntities() const { return this->entities; }

unsigned int EntityManager::GetEntityCount() const { return this->entities.size(); }
