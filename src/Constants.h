#pragma once

namespace Constants {
    constexpr int DEFAULT_SCREEN_WIDTH = 288;
    constexpr int DEFAULT_SCREEN_HEIGHT = 512;
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
    constexpr int PIPE_GAP_START = 130;    // easy opening at score 0
    constexpr int PIPE_GAP_MIN = 80;       // hardest opening
    constexpr int PIPE_GAP_VARIANCE = 15;  // +/- random per pipe
    constexpr int PIPE_GAP_RAMP_SCORE = 30; // score at which gap reaches minimum
    constexpr int PIPE_SPACING = 180;
    constexpr int PIPE_SPACING_VARIANCE = 30; // +/- random per pipe
    constexpr float PIPE_SPEED = 120.0f;

    constexpr int HITBOX_SHRINK = 3;

    constexpr float RESTART_COOLDOWN = 0.5f;

    constexpr int DIGIT_WIDTH = 24;
    constexpr int DIGIT_HEIGHT = 36;

    constexpr float MAX_DT = 0.05f;

    constexpr int GROUND_TILE_WIDTH = 336;
}
