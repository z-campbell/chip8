

#include <stdio.h>
#include "chip8.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Chip8 myChip8;
Mix_Chunk *beep_tone = Mix_LoadWAV("Beep1.wav");
SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(chunk_effect);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return status;
}

void initScreen(void) {

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
void init_I_O(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

void initSound(void) {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        printf("ERROR Opening SDL_Mixer: %s\n", SDL_GetError());

}