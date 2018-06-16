
#include <time.h>
#include "chip8.h"
#include "opcodes.h"
unsigned char chip8_fontset[80] =
        {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };


void initializeChip8(Chip8 *chip8, FILE *game) {

    // Set all timers, PC, SP, and other data to default values

    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->I = 0;
    chip8->PC = GAME_START;
    chip8->SP = chip8->stack[0];
    chip8->cycle_counter = 0;
    chip8->cpu_state = RUN;

    // Clear all registers and memory.
    int i;

    // Clear memory
    for (i = 0; i < MEMORY_SIZE; i++) {
        chip8->memory[i] = 0;
    }

    // Clear Registers, Stack, and Key States
    for (i = 0; i < NUM_KEYS; i++) {
        chip8->key_state[i] = 0;
        chip8->V[i] = 0;
        chip8->stack[i] = 0;
    }

    // Clear Screen

    for (i = 0; i < SCREEN_RESOLUTION; i++) {
        chip8->gfx[i] = 0;
    }

    // Load Font Set Into Proper Memory
    for (i = 0; i < 80; i++) {
        chip8->memory[i] = chip8_fontset[i];
    }
    // Load Game into Memory
    if (game) {
        // Assume that the game is loaded contiguosly into memory
        i = 0;
        unsigned char *ptr = 0;
        while (i < MAX_GAME_SIZE && (*ptr != EOF)) {

            fscanf(game, "%c", ptr);
            chip8->memory[GAME_START + i] = *ptr;
        }
    }


}

void emulateCycle(Chip8 *chip8) {

    unsigned char opcode = 0;
    static void *function = NULL;
    unsigned char retval;

    clock_t current = 0;

    // In halt state, execute the same opcode.
    if (chip8->cpu_state == HALT) {
        executeOpCode(function, chip8->current_opcode);
        if (clock() - (chip8->clock) > 1 / 60) {
            updateTimers(chip8);
            chip8->clock = clock();
        }
        return;
    }

    //else cpu is in RUN state
    opcode = fetchOpCode(chip8);

    if (opcode != EOF && opcode != NULL) {
        function = decodeOpCode(opcode);
    } else {
        function = &errorFunction;
    }

    executeOpCode(function, opcode);
    // Increment PC
    chip8->PC += 2;
    current = clock();

    if (current - (chip8->clock) > 1 / 60) {
        updateTimers(chip8);
        chip8->clock = clock();
    }
}

void updateTimers(Chip8 *chip8) {
    chip8->delay_timer++;

    if (chip8->sound_timer == 65535) {
        beep();
    }

}

void checkKeys(Chip8 *chip8) {

}

unsigned short fetchOpCode(Chip8 *chip8) {
    unsigned short opcode = (chip8->memory[chip8->PC] << 8 | chip8->memory[chip8->PC + 1]);
    chip8->current_opcode = opcode & 0xFFFF;
    return opcode;
}

void *decodeOpCode(unsigned short opcode) {
    unsigned short i;
    while (opcode != CHIP8_OPCODES[i]->code && i < MAX_OPCODES) i++;
    return CHIP8_OPCODES[i]->function;
}

// Definitely needs to be tested but should work...
void executeOpCode(void *function, unsigned short opcode) {

    void (*pfunction)(unsigned short);
    pfunction = function;
    pfunction(opcode);

}

void errorFunction(void) {

    printf("ERROR - OPCODE INVALID");

}
