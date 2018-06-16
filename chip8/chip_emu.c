

#include <stdio.h>
#include "chip8.h"
#include "chip_emu.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
Chip8 myChip8;
Mix_Chunk *beep_tone;
SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;


int main(int argc, char *argv[]) {

    FILE *game_file = NULL;
    unsigned char status;
    if (argc > 0) {
        game_file = fopen(argv[0], "b");
    } else {
        game_file = fopen(DEFAULT_GAME, "b");
    }

    initializeChip8(&myChip8, game_file);

    while (1) {
        SDL_PollEvent(&event);
        clearKeys(&myChip8);
        myChip8.clock = clock();
        if (event.type == SDL_QUIT)
            break;
        switch (event.type) {
            case (SDL_KEYDOWN):
                switch (event.key.keysym.sym)
                    case (KEY_0):
                        myChip8.key_state[0] = 1;
            case (KEY_1):
                myChip8.key_state[1] = 1;
            case (KEY_2):
                myChip8.key_state[2] = 1;
            case (KEY_3):
                myChip8.key_state[3] = 1;
            case (KEY_4):
                myChip8.key_state[4] = 1;
            case (KEY_5):
                myChip8.key_state[5] = 1;
            case (KEY_6):
                myChip8.key_state[6] = 1;
            case (KEY_7):
                myChip8.key_state[7] = 1;
            case (KEY_8):
                myChip8.key_state[8] = 1;
            case (KEY_9):
                myChip8.key_state[9] = 1;
            case (KEY_A):
                myChip8.key_state[0xA] = 1;
            case (KEY_B):
                myChip8.key_state[0xB] = 1;
            case (KEY_C):
                myChip8.key_state[0xC] = 1;
            case (KEY_D):
                myChip8.key_state[0xD] = 1;
            case (KEY_E):
                myChip8.key_state[0xE] = 1;
            case (KEY_F):
                myChip8.key_state[0xF] = 1;

        }

        emulateCycle(&myChip8);
        if (myChip8.draw_flag == 1)
            updateScreen();
        while ((clock() - myChip8.clock) < EMU_CYCLE);

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(beep_tone);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return status;
}

void clearKeys(Chip8 *chip8) {
    for (int i = 0; i < NUM_KEYS; i++) {
        chip8->key_state[i] = 0;
    }
}

void initScreen(void) {

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void DrawPixel(unsigned short x, unsigned short y, unsigned char val) {
    if (val == 0)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void init_I_O(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    initScreen();
    initSound();
}

void initSound(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        printf("ERROR Opening SDL_Mixer: %s\n", SDL_GetError());
    beep_tone = Mix_LoadWAV("Beep1.wav");

    if (beep_tone)
        printf("Beep tone loaded\n");

}

void beep(void) {
    Mix_PlayChannel(-1, beep_tone, 0);
}

void updateScreen(void) {

}

/*
 * Prints list of games in games directory.
 */
void promptGames(void) {

}