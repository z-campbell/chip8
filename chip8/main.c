

#include <stdio.h>
#include "chip8.h"
#include "globals.h"
#ifdef __MACH__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
Chip8 myChip8;
Mix_Chunk *beep_tone;
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
        game_file = fopen(DEFAULT_GAME, "b");
    }

    initializeChip8(&myChip8, game_file);
    setupGraphics();
    setupInput();

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        switch(event.type) {
            case (SDL_KEYDOWN):
                switch (event.key.keysym.sym)
                    case (KEY_0):
                        myChip8.key_state[0] = 1;
                    case (KEY_1):
                        myChip8.key_state[1] = 1;
                    
            }
        emulateCycle(&myChip8);
    }


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
    beep_tone = Mix_LoadWAV("Beep1.wav");

    if(beep_tone)
        printf("Beep tone loaded\n");

}

void beep(void) {
    Mix_PlayChannel(-1, beep_tone, 0);
}