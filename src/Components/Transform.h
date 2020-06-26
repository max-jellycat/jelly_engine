#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include "../EntityManager.h"
#include "../Component.h"
#include "../Game.h"

class Transform : public Component {
public:
    glm::vec2 position{};
    glm::vec2 velocity{};
    int scale;
    int width;
    int height;

public:
    Transform(int posX, int posY, int velX, int velY, int w, int h, int scale) {
        this->position = glm::vec2(posX, posY);
        this->velocity = glm::vec2(velX, velY);
        this->scale = scale;
        this->width = w;
        this->height = h;
    }

    void Init() override {};

    void Update(float deltaTime) override {
        this->position.x += this->velocity.x * deltaTime;
        this->position.y += this->velocity.y * deltaTime;
    }

    void Render() override {}
};
