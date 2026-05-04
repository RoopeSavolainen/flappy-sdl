#include "Game.h"
#include "Constants.h"
#include <algorithm>
#include <cstdio>

Game::Game(int screenW, int screenH)
    : m_screenW(screenW), m_screenH(screenH),
      m_bird(screenH), m_rng(std::random_device{}()) {}

bool Game::init() {
    char* basePath = SDL_GetBasePath();
    if (basePath) {
        m_assetDir = std::string(basePath) + "assets/images/";
        SDL_free(basePath);
    } else {
        m_assetDir = "assets/images/";
    }

    if (!m_renderer.init(m_screenW, m_screenH, m_assetDir)) {
        return false;
    }

    resetGame();
    return true;
}

void Game::resetGame() {
    m_bird.reset();
    m_pipes.clear();
    m_score = 0;
    m_groundOffset = 0.0f;
    m_stateTime = 0.0f;
    m_flashAlpha = 0.0f;
}

void Game::run() {
    Uint32 lastTick = SDL_GetTicks();

    while (m_running) {
        Uint32 now = SDL_GetTicks();
        float dt = static_cast<float>(now - lastTick) / 1000.0f;
        dt = std::min(dt, Constants::MAX_DT);
        lastTick = now;

        processEvents();
        update(dt);
        render();

        SDL_Delay(1);
    }
}

void Game::processEvents() {
    m_clicked = false;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            m_running = false;
        } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            m_clicked = true;
        }
    }
}

void Game::update(float dt) {
    m_stateTime += dt;

    switch (m_state) {
    case GameState::Start:
        m_bird.updateBob(m_stateTime);
        m_groundOffset += Constants::PIPE_SPEED * dt;

        if (m_clicked) {
            m_state = GameState::Playing;
            m_stateTime = 0.0f;
            m_bird.reset();
            m_bird.flap();
            // Spawn pipes to fill the screen
            while (needsMorePipes()) {
                spawnPipe();
            }
        }
        break;

    case GameState::Playing:
        m_bird.update(dt);
        m_groundOffset += Constants::PIPE_SPEED * dt;

        if (m_clicked) {
            m_bird.flap();
        }

        for (auto& pipe : m_pipes) {
            pipe.update(dt);

            // Score check
            if (!pipe.scored && pipe.getX() + Constants::PIPE_WIDTH < Constants::BIRD_X) {
                pipe.scored = true;
                m_score++;
            }
        }

        // Remove off-screen pipes
        while (!m_pipes.empty() && m_pipes.front().isOffScreen()) {
            m_pipes.erase(m_pipes.begin());
        }

        // Spawn new pipes as needed
        while (needsMorePipes()) {
            spawnPipe();
        }

        if (checkCollision()) {
            m_state = GameState::GameOver;
            m_stateTime = 0.0f;
            m_flashAlpha = 1.0f;
        }
        break;

    case GameState::GameOver:
        // Fade out flash
        if (m_flashAlpha > 0.0f) {
            m_flashAlpha -= dt * 3.0f;
            if (m_flashAlpha < 0.0f) m_flashAlpha = 0.0f;
        }

        // Bird falls to ground
        {
            float groundY = static_cast<float>(m_screenH - Constants::GROUND_HEIGHT - Constants::BIRD_HEIGHT);
            if (m_bird.getY() < groundY) {
                m_bird.update(dt);
            }
        }

        if (m_clicked && m_stateTime > Constants::RESTART_COOLDOWN) {
            resetGame();
            m_state = GameState::Start;
            m_stateTime = 0.0f;
        }
        break;
    }
}

void Game::render() {
    m_renderer.clear();
    m_renderer.drawBackground();

    // Draw pipes behind ground
    for (const auto& pipe : m_pipes) {
        m_renderer.drawPipe(pipe);
    }

    m_renderer.drawGround(m_groundOffset);
    m_renderer.drawBird(m_bird);

    switch (m_state) {
    case GameState::Start:
        m_renderer.drawMessage();
        break;
    case GameState::Playing:
        m_renderer.drawScore(m_score);
        break;
    case GameState::GameOver:
        m_renderer.drawScore(m_score);
        m_renderer.drawGameOver();
        m_renderer.drawFlash(m_flashAlpha);
        break;
    }

    m_renderer.present();
}

bool Game::needsMorePipes() const {
    if (m_pipes.empty()) return true;
    return m_pipes.back().getX() < m_screenW + Constants::PIPE_SPACING;
}

void Game::spawnPipe() {
    float lastX = static_cast<float>(m_screenW);
    if (!m_pipes.empty()) {
        lastX = m_pipes.back().getX() + Constants::PIPE_SPACING;
    }

    // Random gap center between reasonable bounds
    int minY = Constants::PIPE_GAP / 2 + Constants::PIPE_CAP_HEIGHT + 20;
    int maxY = m_screenH - Constants::GROUND_HEIGHT - Constants::PIPE_GAP / 2 - Constants::PIPE_CAP_HEIGHT - 20;

    std::uniform_int_distribution<int> dist(minY, maxY);
    int gapCenter = dist(m_rng);

    m_pipes.emplace_back(lastX, gapCenter, m_screenH);
}

bool Game::checkCollision() {
    SDL_Rect birdHitbox = m_bird.getHitbox();

    // Ground collision
    int groundY = m_screenH - Constants::GROUND_HEIGHT;
    if (birdHitbox.y + birdHitbox.h >= groundY) {
        return true;
    }

    // Ceiling collision
    if (birdHitbox.y <= 0) {
        return true;
    }

    // Pipe collision
    for (const auto& pipe : m_pipes) {
        SDL_Rect topBody = pipe.getTopRect();
        SDL_Rect topCap = pipe.getTopCapRect();
        SDL_Rect bottomBody = pipe.getBottomRect();
        SDL_Rect bottomCap = pipe.getBottomCapRect();

        if (SDL_HasIntersection(&birdHitbox, &topBody) ||
            SDL_HasIntersection(&birdHitbox, &topCap) ||
            SDL_HasIntersection(&birdHitbox, &bottomBody) ||
            SDL_HasIntersection(&birdHitbox, &bottomCap)) {
            return true;
        }
    }

    return false;
}
