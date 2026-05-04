#include "Bird.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>

Bird::Bird() {
    reset();
}

void Bird::reset() {
    m_y = Constants::SCREEN_HEIGHT / 2.0f - Constants::BIRD_HEIGHT / 2.0f;
    m_velocity = 0.0f;
    m_frame = 0;
    m_frameTimer = 0.0f;
}

void Bird::flap() {
    m_velocity = Constants::FLAP_VELOCITY;
}

void Bird::update(float dt) {
    m_velocity += Constants::GRAVITY * dt;
    m_velocity = std::min(m_velocity, Constants::MAX_VELOCITY);
    m_y += m_velocity * dt;

    m_frameTimer += dt;
    if (m_frameTimer >= Constants::BIRD_ANIM_SPEED) {
        m_frameTimer -= Constants::BIRD_ANIM_SPEED;
        m_frame = (m_frame + 1) % Constants::BIRD_FRAMES;
    }
}

void Bird::updateBob(float time) {
    float baseY = Constants::SCREEN_HEIGHT / 2.0f - Constants::BIRD_HEIGHT / 2.0f;
    m_y = baseY + std::sin(time * 3.0f) * 10.0f;

    m_frameTimer += 0.016f;
    if (m_frameTimer >= Constants::BIRD_ANIM_SPEED) {
        m_frameTimer -= Constants::BIRD_ANIM_SPEED;
        m_frame = (m_frame + 1) % Constants::BIRD_FRAMES;
    }
}

SDL_Rect Bird::getRect() const {
    return {
        static_cast<int>(Constants::BIRD_X),
        static_cast<int>(m_y),
        Constants::BIRD_WIDTH,
        Constants::BIRD_HEIGHT
    };
}

SDL_Rect Bird::getHitbox() const {
    return {
        static_cast<int>(Constants::BIRD_X) + Constants::HITBOX_SHRINK,
        static_cast<int>(m_y) + Constants::HITBOX_SHRINK,
        Constants::BIRD_WIDTH - 2 * Constants::HITBOX_SHRINK,
        Constants::BIRD_HEIGHT - 2 * Constants::HITBOX_SHRINK
    };
}

int Bird::getFrame() const {
    return m_frame;
}

float Bird::getRotation() const {
    // Map velocity to rotation angle
    // Going up: -30 degrees, falling: up to +90 degrees
    float angle = m_velocity / Constants::MAX_VELOCITY * 90.0f;
    return std::clamp(angle, -30.0f, 90.0f);
}
