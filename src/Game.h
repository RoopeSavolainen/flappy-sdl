#pragma once

#include "Bird.h"
#include "Pipe.h"
#include "Renderer.h"
#include <vector>
#include <string>
#include <random>

enum class GameState { Start, Playing, GameOver };

class Game {
public:
    Game();
    ~Game() = default;

    bool init();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    void resetGame();
    void spawnPipe();
    bool checkCollision();

    std::string m_assetDir;
    Renderer m_renderer;
    Bird m_bird;
    std::vector<Pipe> m_pipes;
    GameState m_state = GameState::Start;

    int m_score = 0;
    float m_groundOffset = 0.0f;
    float m_stateTime = 0.0f; // time in current state
    float m_flashAlpha = 0.0f;
    bool m_running = true;
    bool m_clicked = false;

    std::mt19937 m_rng;
};
