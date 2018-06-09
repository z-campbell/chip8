//
//  chip8.c
//  chip8
//
//  Created by Zach Campbell on 5/28/18.
//  Copyright © 2018 Zach Campbell. All rights reserved.
//
#include <time.h>
#include "chip8.h"
#include "opcodes.h"

const clock_t emu_start = clock();


void initializeChip8( Chip8 *chip8, FILE *game ) {

    // Set all timers, PC, SP, and other data to default values
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->I = 0;
    chip8->PC = GAME_START;
    chip8->SP = chip8->stack[0];
    chip8->cycle_counter = 0;

    // Clear all registers and memory.
    int i;

    // Clear memory
    for (i = 0; i < MEMORY_SIZE; i++) {
        chip8->memory[i] = 0;
    }

    // Clear Registers, Stack, and Key States
    for(i = 0; i < NUM_KEYS; i++) {
        chip8->key_state[i] = 0;
        chip8->V[i] = 0;
        chip8->stack[i] = 0;
    }

    // Clear Screen

    for (i = 0; i < SCREEN_RESOLUTION; i++) {
        chip8->gfx[i] = 0;
    }

    // Load Game into Memory
    if (game) {
        // Assume that the game is loaded contiguosly into memory
        i = 0;
        unsigned char *ptr = 0;
        while ( i < MAX_GAME_SIZE && *ptr != EOF) {

            fscanf(game, "%c", ptr);
            chip8->memory[GAME_START + i] = *ptr;
        }
    }




}

void emulateCycle (Chip8 *chip8) {

    unsigned char opcode = 0;
    void *function = NULL;
    unsigned char retval;

    clock_t current = 0;
    // Fetch Next OP Code
    opcode = fetchOpCode(chip8);

    if (opcode != EOF && opcode != NULL) {
        function = decodeOpCode(opcode);


    }
    else {
        function = &errorFunction;
    }

    executeOpCode(function, opcode);
    chip8->PC += 2;
    current = clock();

    if (current - emu_start > 1/60) {
        updateTimers(chip8);
        emu_start = clock();
    }
}

void updateTimers (Chip8 *chip8) {
    chip8->delay_timer++;

    if (chip8->sound_timer == 65535 )
    {
        beep();
    }

}

void checkKeys (Chip8 *chip8) {

}

unsigned short fetchOpCode (Chip8 *chip8) {
    unsigned short opcode = (chip8->memory[chip8->PC] << 8 | chip8->memory[chip8->PC + 1 ]);

    return opcode;
}

void *decodeOpCode (unsigned short opcode) {

}

// Definitely needs to be tested but should work...
void executeOpCode (void *function, unsigned short opcode) {

    void (*pfunction)(unsigned short);
    pfunction = function;
    pfunction(opcode);

}

void beep (void) {

}
void errorFunction ( void )
{

    printf("ERROR - OPCODE INVALID");

}
