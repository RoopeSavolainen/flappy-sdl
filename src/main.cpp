#include "Game.h"
#include "Constants.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int screenW = Constants::DEFAULT_SCREEN_WIDTH;
    int screenH = Constants::DEFAULT_SCREEN_HEIGHT;

    if (argc == 3) {
        screenW = std::atoi(argv[1]);
        screenH = std::atoi(argv[2]);
        if (screenW <= 0 || screenH <= 0) {
            std::fprintf(stderr, "Usage: %s [width height]\n", argv[0]);
            return 1;
        }
    } else if (argc != 1) {
        std::fprintf(stderr, "Usage: %s [width height]\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    Game game(screenW, screenH);
    int exitCode = 0;

    if (game.init()) {
        game.run();
    } else {
        std::fprintf(stderr, "Game init failed\n");
        exitCode = 1;
    }

    SDL_Quit();
    return exitCode;
}
