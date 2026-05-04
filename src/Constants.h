#pragma once

#include <cstdint>

namespace Constants {
    constexpr int SCREEN_WIDTH = 288;
    constexpr int SCREEN_HEIGHT = 512;
    constexpr int GROUND_HEIGHT = 56;

    constexpr int BIRD_WIDTH = 34;
    constexpr int BIRD_HEIGHT = 24;
    constexpr int BIRD_FRAMES = 3;
    constexpr float BIRD_X = 80.0f;
    constexpr float GRAVITY = 980.0f;
    constexpr float FLAP_VELOCITY = -280.0f;
    constexpr float MAX_VELOCITY = 400.0f;
    constexpr float BIRD_ANIM_SPEED = 0.1f; // seconds per frame

    constexpr int PIPE_WIDTH = 52;
    constexpr int PIPE_CAP_HEIGHT = 26;
    constexpr int PIPE_GAP = 100;
    constexpr int PIPE_SPACING = 180;
    constexpr float PIPE_SPEED = 120.0f;

    constexpr int HITBOX_SHRINK = 3;

    constexpr float RESTART_COOLDOWN = 0.5f;

    constexpr int DIGIT_WIDTH = 24;
    constexpr int DIGIT_HEIGHT = 36;

    constexpr float MAX_DT = 0.05f;

    constexpr int GROUND_TILE_WIDTH = 336;
}
