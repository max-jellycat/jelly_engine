#pragma once

#include <SDL.h>
#include <iostream>
#include "Transform.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include "Animator.h"

class Sprite : public Component {
private:
    Transform *m_transform{};
    SDL_Texture *m_texture{};
    Animator *m_animator;
    SDL_Rect m_sourceRect{};
    SDL_Rect m_destRect{};
    bool m_isAnimated;
    bool m_isFixed;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    explicit Sprite(const std::string& id) {
        m_isFixed = false;
        m_isAnimated = false;
        SetTexture(id);
    }

    Sprite(const std::string& id, bool isAnimated, bool isFixed) {
        m_isFixed = isFixed;
        m_isAnimated = isAnimated;
        SetTexture(id);
    }

    void SetTexture(const std::string& assetTextureId) {
        m_texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Init() override {
        m_transform = owner->GetComponent<Transform>();
        m_sourceRect.x = 0;
        m_sourceRect.y = 0;
        m_sourceRect.w = m_transform->width;
        m_sourceRect.h = m_transform->height;
    }

    void Update(float deltaTime) override {
        m_animator = owner->GetComponent<Animator>();
        if (m_animator) {
            m_sourceRect.x = m_sourceRect.w * static_cast<int>((SDL_GetTicks() / m_animator->getAnimationSpeed()) % m_animator->getAnimationFrames());
            m_sourceRect.y = m_animator->getAnimationIndex() * m_transform->height;
        }

        m_destRect.x = static_cast<int>(m_transform->position.x);
        m_destRect.y = static_cast<int>(m_transform->position.y);
        m_destRect.w = m_transform->width * m_transform->scale;
        m_destRect.h = m_transform->height * m_transform->scale;
    }

    void Render() override {
        TextureManager::Draw(m_texture, m_sourceRect, m_destRect, spriteFlip);
    }
};
