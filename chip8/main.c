

#include <stdio.h>
#include "chip8.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Chip8 myChip8;

int main(int argc, const char * argv[]) {

    FILE  *game_file = NULL;
    unsigned char status;
    if (argc > 0) {
            game_file = fopen(argv[0], "b");
    }
    else {
        game_file = DEFAULT_GAME;
    }

    initializeChip8(&myChip8, game_file);
    setupGraphics();
    setupInput();

    status = runChip8(&myChip8);


    return status;
}

void initScreen(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void DrawPixel( unsigned short x, unsigned short y, unsigned char val) {
    if (val == 0)
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    else
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderDrawPoint(renderer, x, y);
}