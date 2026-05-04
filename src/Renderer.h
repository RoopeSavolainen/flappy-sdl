#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <array>

class Bird;
class Pipe;

class Renderer {
public:
    Renderer();
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool init(int screenW, int screenH, const std::string& assetDir);
    void clear();
    void present();

    void drawBackground();
    void drawGround(float offset);
    void drawBird(const Bird& bird);
    void drawPipe(const Pipe& pipe);
    void drawScore(int score);
    void drawMessage();    // "Click to play"
    void drawGameOver();
    void drawFlash(float alpha); // white flash overlay

    SDL_Renderer* getSDLRenderer() { return m_renderer; }

private:
    SDL_Texture* loadTexture(const std::string& path, bool colorKey = false);

    int m_screenW = 0;
    int m_screenH = 0;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    SDL_Texture* m_background = nullptr;
    SDL_Texture* m_ground = nullptr;
    SDL_Texture* m_bird = nullptr;
    SDL_Texture* m_pipe = nullptr;
    SDL_Texture* m_pipeCap = nullptr;
    std::array<SDL_Texture*, 10> m_digits{};
    SDL_Texture* m_gameover = nullptr;
    SDL_Texture* m_message = nullptr;

    // Store texture dimensions for rendering
    int m_messageW = 0, m_messageH = 0;
    int m_gameoverW = 0, m_gameoverH = 0;
};
