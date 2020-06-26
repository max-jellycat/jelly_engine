#pragma once

#include <SDL.h>
#include "Transform.h"
#include "../TextureManager.h"
#include "../Animation.h"

class Sprite : public Component {
private:
    Transform *m_transform{};
    SDL_Texture *m_texture{};
    SDL_Rect m_sourceRect{};
    SDL_Rect m_destRect{};
    bool m_isAnimated;
    int m_nFrames{};
    int m_animationSpeed{};
    bool m_isFixed;
    std::map<std::string, Animation> m_animations;
    std::string m_currentAnimationName;
    int m_animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    explicit Sprite(const std::string& textureId) {
        m_isAnimated = false;
        m_isFixed = false;
        SetTexture(textureId);
    }

    Sprite(const std::string& id, int nFrames, int animationSpeed, bool hasDirections, bool isFixed) {
        m_isAnimated = true;
        m_isFixed = isFixed;
        m_nFrames = nFrames;
        m_animationSpeed = animationSpeed;

        if (hasDirections) {
            Animation downAnimation(0, nFrames, animationSpeed);
            Animation rightAnimation(1, nFrames, animationSpeed);
            Animation leftAnimation(2, nFrames, animationSpeed);
            Animation upAnimation(3, nFrames, animationSpeed);

            m_animations.emplace("DownAnimation", downAnimation);
            m_animations.emplace("RightAnimation", rightAnimation);
            m_animations.emplace("LeftAnimation", leftAnimation);
            m_animations.emplace("UpAnimation", upAnimation);

            m_animationIndex = 0;
            m_currentAnimationName = "DownAnimation";
        } else {
            Animation singleAnimation(0, nFrames, animationSpeed);
            m_animations.emplace("SingleAnimation", singleAnimation);
            m_animationIndex = 0;
            m_currentAnimationName = "SingleAnimation";
        }

        Play(m_currentAnimationName);
        SetTexture(id);
    }

    void Play(const std::string& animationName) {
        m_nFrames = m_animations[animationName].getFrames();
        m_animationIndex = m_animations[animationName].getIndex();
        m_animationSpeed = m_animations[animationName].getAnimationSpeed();
        m_currentAnimationName = animationName;
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
        if (m_isAnimated) {
            m_sourceRect.x = m_sourceRect.w * static_cast<int>((SDL_GetTicks() / m_animationSpeed) % m_nFrames);
        }

        m_sourceRect.y = m_animationIndex * m_transform->height;

        m_destRect.x = static_cast<int>(m_transform->position.x);
        m_destRect.y = static_cast<int>(m_transform->position.y);
        m_destRect.w = m_transform->width * m_transform->scale;
        m_destRect.h = m_transform->height * m_transform->scale;
    }

    void Render() override {
        TextureManager::Draw(m_texture, m_sourceRect, m_destRect, spriteFlip);
    }
};
