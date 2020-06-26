#pragma once

#include "Entity.h"

class Entity;

class Component {
public:
    Entity *owner;

    virtual ~Component() {};

    virtual void Init() {};

    virtual void Update(float deltaTime) {};

    virtual void Render() {};
};