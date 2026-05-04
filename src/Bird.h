#pragma once

#include <SDL2/SDL.h>

class Bird {
public:
    Bird(int screenH);

    void reset();
    void flap();
    void update(float dt);
    void updateBob(float time); // for start screen bobbing

    SDL_Rect getRect() const;
    SDL_Rect getHitbox() const;
    int getFrame() const;
    float getRotation() const;
    float getY() const { return m_y; }

private:
    int m_screenH;
    float m_y;
    float m_velocity;
    int m_frame;
    float m_frameTimer;
};
