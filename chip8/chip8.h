//
//  chip8.h
//  chip8
//
//  Created by Zach Campbell on 5/28/18.
//  Copyright © 2018 Zach Campbell. All rights reserved.
//

#ifndef chip8_h
#define chip8_h

#include <stdio.h>

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define SCREEN_RESOLUTION 64*32
#define STACK_SIZE 16
#define NUM_KEYS 16

#define MAX_GAME_SIZE (0x0EA0 - 0x0200)
#define GAME_START 0x0200
#define MAX_GAME_ADDR 0x0EA0
#define DEFAULT_GAME "pong.ROM"

enum {
    STACK_UNDERFLOW,
    STACK_OVERFLOW,
    DRAW_FLAG,

};

typedef struct Chip8 {

    unsigned char memory[MEMORY_SIZE];        // Main memory, see README for memory map.
    unsigned char V[NUM_REGISTERS];          // Registers, 0-F, V[F] should only be used as carry
    unsigned char gfx[SCREEN_RESOLUTION];   // Screen array, total of 64*32 pixels = 2048
    unsigned short I;                       // Index Register
    unsigned short PC;                     // Program counter
    unsigned short SP;                    // Program SP
    unsigned short stack[STACK_SIZE];    // Program Stack, memory map gives
    unsigned short delay_timer;         // Delay Timer, 60 Hz
    unsigned short sound_timer;         // Sound Time, 60Hz, will beep when underflow (1)
    unsigned char key_state[NUM_KEYS];  // Key state
    FILE *game;
    clock_t clock;
    unsigned short status_flag;
    double cycle_counter;
    unsigned short current_opcode;
    unsigned char draw_flag;


} Chip8;

void  *function_ptr (void);
void loadGame(FILE *file);
void initializeChip8(Chip8 *chip8, FILE *game);
void emulateCycle(Chip8 *chip8);
int runChip8(Chip8 *chip8);

void updateTimers(Chip8 *chip8);
unsigned short fetchOpCode (Chip8 *chip8);
void *decodeOpCode (unsigned short opcode);
void executeOpCode ( void *function, unsigned short opcode);
void checkKeys (Chip8 *chip8);

void beep (void);

void errorFunction(void);

#endif /* chip8_h */
