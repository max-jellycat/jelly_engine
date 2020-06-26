#pragma once

#include <SDL.h>
#include "../Component.h"
#include "Transform.h"
#include "../TextureManager.h"

class Sprite : public Component {
private:
    Transform *transform{};
    SDL_Texture *texture{};
    SDL_Rect sourceRect{};
    SDL_Rect destRect{};

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    explicit Sprite(const std::string& textureId) {
        SetTexture(textureId);
    }

    void SetTexture(const std::string& assetTextureId) {
        texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Init() override {
        transform = owner->GetComponent<Transform>();
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = transform->width;
        sourceRect.h = transform->height;
    }

    void Update(float deltaTime) override {
        destRect.x = (int) transform->position.x;
        destRect.y = (int) transform->position.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void Render() override {
        TextureManager::Draw(texture, sourceRect, destRect, spriteFlip);
    }
};
