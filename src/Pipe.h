#pragma once

#include <SDL2/SDL.h>

class Pipe {
public:
    Pipe(float x, int gapCenterY, int screenH);

    void update(float dt);
    bool isOffScreen() const;

    SDL_Rect getTopRect() const;
    SDL_Rect getBottomRect() const;
    SDL_Rect getTopCapRect() const;
    SDL_Rect getBottomCapRect() const;
    float getX() const { return m_x; }

    bool scored = false;

private:
    float m_x;
    int m_gapCenterY;
    int m_screenH;
};
