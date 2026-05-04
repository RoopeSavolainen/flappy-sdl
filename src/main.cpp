#include "Game.h"
#include <SDL2/SDL.h>
#include <cstdio>

int main(int /*argc*/, char* /*argv*/[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    Game game;
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
