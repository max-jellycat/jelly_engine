#include "Animation.h"

Animation::Animation(int index, int nFrames, int animationSpeed)
        : m_index(index), m_nFrames(nFrames), m_animationSpeed(animationSpeed) {}

int Animation::getIndex() const { return m_index; }

int Animation::getFrames() const { return m_nFrames; }

int Animation::getAnimationSpeed() const { return m_animationSpeed; }
