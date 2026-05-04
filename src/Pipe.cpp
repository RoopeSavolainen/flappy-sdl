#include "Pipe.h"
#include "Constants.h"

Pipe::Pipe(float x, int gapCenterY, int gapSize, int screenH)
    : m_x(x), m_gapCenterY(gapCenterY), m_gapSize(gapSize), m_screenH(screenH) {}

void Pipe::update(float dt) {
    m_x -= Constants::PIPE_SPEED * dt;
}

bool Pipe::isOffScreen() const {
    return m_x + Constants::PIPE_WIDTH < 0;
}

SDL_Rect Pipe::getTopRect() const {
    int bottomOfTop = m_gapCenterY - m_gapSize / 2;
    return {
        static_cast<int>(m_x),
        0,
        Constants::PIPE_WIDTH,
        bottomOfTop - Constants::PIPE_CAP_HEIGHT
    };
}

SDL_Rect Pipe::getBottomRect() const {
    int topOfBottom = m_gapCenterY + m_gapSize / 2;
    return {
        static_cast<int>(m_x),
        topOfBottom + Constants::PIPE_CAP_HEIGHT,
        Constants::PIPE_WIDTH,
        m_screenH - Constants::GROUND_HEIGHT - topOfBottom - Constants::PIPE_CAP_HEIGHT
    };
}

SDL_Rect Pipe::getTopCapRect() const {
    int bottomOfTop = m_gapCenterY - m_gapSize / 2;
    return {
        static_cast<int>(m_x) - 2,
        bottomOfTop - Constants::PIPE_CAP_HEIGHT,
        Constants::PIPE_WIDTH + 4,
        Constants::PIPE_CAP_HEIGHT
    };
}

SDL_Rect Pipe::getBottomCapRect() const {
    int topOfBottom = m_gapCenterY + m_gapSize / 2;
    return {
        static_cast<int>(m_x) - 2,
        topOfBottom,
        Constants::PIPE_WIDTH + 4,
        Constants::PIPE_CAP_HEIGHT
    };
}
