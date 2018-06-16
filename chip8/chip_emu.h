//
// Created by Zach Campbell on 6/15/18.
//

#ifndef CHIP8_CHIP_EMU_H
#define CHIP8_CHIP_EMU_H
#ifdef __MACH__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

// Emulator cycle is at 1000 Hz or 1 ms
#define EMU_CYCLE 1

#define KEY_0 SDLK_x
#define KEY_1 SDLK_1
#define KEY_2 SDLK_2
#define KEY_3 SDLK_3
#define KEY_4 SDLK_q
#define KEY_5 SDLK_w
#define KEY_6 SDLK_e
#define KEY_7 SDLK_a
#define KEY_8 SDLK_s
#define KEY_9 SDLK_d
#define KEY_A SDLK_z
#define KEY_B SDLK_c
#define KEY_C SDLK_4
#define KEY_D SDLK_r
#define KEY_E SDLK_f
#define KEY_F SDLK_v



#endif //CHIP8_CHIP_EMU_H
