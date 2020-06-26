#pragma once

#include <map>
#include <string>
#include "../Animation.h"
#include "../Component.h"
#include "Sprite.h"

class Sprite;

class Animator : public Component {
private:
    std::map<std::string, Animation> m_animations;
    std::string m_currentAnimationName;

public:
    int nFrames{};
    int animationIndex{};
    int animationSpeed{};
    Animator() {};

    Animator(const std::string& animationName, Animation &animation) {
        m_animations.emplace(animationName, animation);
        Play(animationName);
    }
    void AddAnimation(const std::string &animationName, Animation &animation) {
        m_animations.emplace(animationName, animation);
    }

    void Play(const std::string &animationName) {
        nFrames = m_animations[animationName].getFrames();
        animationIndex = m_animations[animationName].getIndex();
        animationSpeed = m_animations[animationName].getAnimationSpeed();
        m_currentAnimationName = animationName;
    }

    std::string getCurrentAnimation() const { return m_currentAnimationName; }

    int getAnimationIndex() const { return animationIndex; }

    int getAnimationFrames() const { return nFrames; }

    int getAnimationSpeed() const { return animationSpeed; }
};
