#include "Renderer.h"
#include "Bird.h"
#include "Pipe.h"
#include "Constants.h"
#include <cstdio>
#include <string>

Renderer::Renderer() {}

Renderer::~Renderer() {
    auto destroy = [](SDL_Texture*& t) { if (t) { SDL_DestroyTexture(t); t = nullptr; } };

    destroy(m_background);
    destroy(m_ground);
    destroy(m_bird);
    destroy(m_pipe);
    destroy(m_pipeCap);
    for (auto& d : m_digits) destroy(d);
    destroy(m_gameover);
    destroy(m_message);

    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
}

bool Renderer::init(int screenW, int screenH, const std::string& assetDir) {
    m_screenW = screenW;
    m_screenH = screenH;

    m_window = SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_screenW, m_screenH,
        SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
    if (!m_renderer) {
        std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return false;
    }

    m_background = loadTexture(assetDir + "background.bmp");
    m_ground = loadTexture(assetDir + "ground.bmp");
    m_bird = loadTexture(assetDir + "bird.bmp", true);
    m_pipe = loadTexture(assetDir + "pipe.bmp");
    m_pipeCap = loadTexture(assetDir + "pipe_cap.bmp");

    for (int i = 0; i < 10; i++) {
        m_digits[i] = loadTexture(assetDir + "digit_" + std::to_string(i) + ".bmp", true);
    }

    m_gameover = loadTexture(assetDir + "gameover.bmp", true);
    m_message = loadTexture(assetDir + "message.bmp", true);

    if (m_message) SDL_QueryTexture(m_message, nullptr, nullptr, &m_messageW, &m_messageH);
    if (m_gameover) SDL_QueryTexture(m_gameover, nullptr, nullptr, &m_gameoverW, &m_gameoverH);

    return true;
}

SDL_Texture* Renderer::loadTexture(const std::string& path, bool colorKey) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        std::fprintf(stderr, "Failed to load %s: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    if (colorKey) {
        SDL_SetColorKey(surface, SDL_TRUE,
            SDL_MapRGB(surface->format, 255, 0, 255));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::fprintf(stderr, "Failed to create texture from %s: %s\n", path.c_str(), SDL_GetError());
    }
    return texture;
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::drawBackground() {
    if (m_background) {
        SDL_RenderCopy(m_renderer, m_background, nullptr, nullptr);
    }
}

void Renderer::drawGround(float offset) {
    if (!m_ground) return;

    int iOffset = static_cast<int>(offset) % Constants::GROUND_TILE_WIDTH;
    int y = m_screenH - Constants::GROUND_HEIGHT;

    // Draw enough tiles to cover the screen
    for (int x = -iOffset; x < m_screenW; x += Constants::GROUND_TILE_WIDTH) {
        SDL_Rect dst{x, y, Constants::GROUND_TILE_WIDTH, Constants::GROUND_HEIGHT};
        SDL_RenderCopy(m_renderer, m_ground, nullptr, &dst);
    }
}

void Renderer::drawBird(const Bird& bird) {
    if (!m_bird) return;

    int frame = bird.getFrame();
    SDL_Rect src{
        frame * Constants::BIRD_WIDTH, 0,
        Constants::BIRD_WIDTH, Constants::BIRD_HEIGHT
    };

    SDL_Rect dst = bird.getRect();
    double angle = bird.getRotation();

    SDL_RenderCopyEx(m_renderer, m_bird, &src, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::drawPipe(const Pipe& pipe) {
    if (!m_pipe || !m_pipeCap) return;

    // Top pipe body (flipped vertically)
    SDL_Rect topBody = pipe.getTopRect();
    if (topBody.h > 0) {
        SDL_RenderCopyEx(m_renderer, m_pipe, nullptr, &topBody, 0, nullptr, SDL_FLIP_VERTICAL);
    }

    // Top pipe cap (flipped vertically)
    SDL_Rect topCap = pipe.getTopCapRect();
    SDL_RenderCopyEx(m_renderer, m_pipeCap, nullptr, &topCap, 0, nullptr, SDL_FLIP_VERTICAL);

    // Bottom pipe body
    SDL_Rect bottomBody = pipe.getBottomRect();
    if (bottomBody.h > 0) {
        SDL_RenderCopy(m_renderer, m_pipe, nullptr, &bottomBody);
    }

    // Bottom pipe cap
    SDL_Rect bottomCap = pipe.getBottomCapRect();
    SDL_RenderCopy(m_renderer, m_pipeCap, nullptr, &bottomCap);
}

void Renderer::drawScore(int score) {
    std::string digits = std::to_string(score);
    int totalW = static_cast<int>(digits.size()) * (Constants::DIGIT_WIDTH + 2);
    int startX = (m_screenW - totalW) / 2;
    int y = 40;

    for (size_t i = 0; i < digits.size(); i++) {
        int d = digits[i] - '0';
        if (d >= 0 && d <= 9 && m_digits[d]) {
            SDL_Rect dst{
                startX + static_cast<int>(i) * (Constants::DIGIT_WIDTH + 2),
                y,
                Constants::DIGIT_WIDTH,
                Constants::DIGIT_HEIGHT
            };
            SDL_RenderCopy(m_renderer, m_digits[d], nullptr, &dst);
        }
    }
}

void Renderer::drawMessage() {
    if (!m_message) return;
    SDL_Rect dst{
        (m_screenW - m_messageW) / 2,
        m_screenH / 3 - m_messageH / 2,
        m_messageW,
        m_messageH
    };
    SDL_RenderCopy(m_renderer, m_message, nullptr, &dst);
}

void Renderer::drawGameOver() {
    if (!m_gameover) return;
    SDL_Rect dst{
        (m_screenW - m_gameoverW) / 2,
        m_screenH / 3 - m_gameoverH / 2,
        m_gameoverW,
        m_gameoverH
    };
    SDL_RenderCopy(m_renderer, m_gameover, nullptr, &dst);
}

void Renderer::drawFlash(float alpha) {
    if (alpha <= 0.0f) return;
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, static_cast<Uint8>(alpha * 255));
    SDL_Rect full{0, 0, m_screenW, m_screenH};
    SDL_RenderFillRect(m_renderer, &full);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
}
