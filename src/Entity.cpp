#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager &manager)
        : manager(manager) {
    this->active = true;
}

Entity::Entity(EntityManager &manager, std::string name)
        : manager(manager), name(name) {
    this->active = true;
}

void Entity::Update(float deltaTime) {
    for (auto &component : this->components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto &component : this->components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->active = false;
}

void Entity::ListComponents() const {
    for (auto &component: this->componentTypeMap) {
        std::cout << "  Component<" << component.first->name() << ">" << std::endl;
    }
}

bool Entity::Active() const { return this->active; }