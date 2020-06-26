#pragma once

class Animation {
private:
    int m_index;
    int m_nFrames;
    int m_animationSpeed;

public:
    Animation() = default;

    Animation(int index, int nFrames, int animationSpeed);

    int getIndex() const;

    int getFrames() const;

    int getAnimationSpeed() const;
};
