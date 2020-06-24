#pragma once

#include "../entities/Entity.h"

class Component
{
public:
    Entity *owner;

public:
    virtual ~Component();
    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render();
};