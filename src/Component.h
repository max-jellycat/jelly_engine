#pragma once

#include "Entity.h"

class Entity;

class Component {
public:
    Entity *owner{};

    virtual ~Component() = default;;

    virtual void Init() {};

    virtual void Update(float deltaTime) {};

    virtual void Render() {};
};