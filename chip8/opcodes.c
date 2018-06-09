#include <stdlib.h>
#include <time.h>
#include "opcodes.h"
#include "opcode_functions.h"
#include "opcodes.h"
#include "chip8.h"

const opcode Call = {
        .code = 0x000,
        .function = &opCall,
};

const opcode DisplayClear = {
        .code = 0x00E0,
        .function = &opDisplayClear,
};

const opcode Return = {
        .code = 0x00EE,
        .function = &opReturn,
};

const opcode Goto = {
        .code = 0x1000,
        .function = &opGoto,
};

const opcode CallSubRoutine = {
        .code = 0x2000,
        .function = &opCallSubRoutine,
};

// Conditional Subroutines

const opcode SkipIfEqN = {
        .code = 0x3000,
        .function = &opSkipIfEqN,
};

const opcode SkipIfnEqN = {
        .code = 0x4000,
        .function = &opSkipIfnEqN,
};

const opcode SkipIfEq = {
        .code = 0x5000,
        .function = &opSkipIfEq,
};

// Assignment opcodes

const opcode SetRegister = {
        .code = 0x6000,
        .function = &opSetRegister,
};

const opcode IncrementRegister = {
        .code = 0x7000,
        .function = &opIncrementRegister,
};

const opcode AssignRegister = {
        .code = 0x8000,
        .function = &opAssignRegister,
};

// Bitwise Operations

const opcode BitOr = {
        .code = 0x8001,
        .function = &opBitOr,
};

const opcode BitAnd = {
        .code = 0x8002,
        .function = &opBitAnd,
};

const opcode BitXor = {
        .code = 0x8003,
        .function = &opBitXor,
};

// Arithmetic Operators

const opcode AddXY = {
        .code = 0x8004,
        .function = &opAddXY,
};
//
const opcode DecrimentXY = {
        .code = 0x8005,
        .function = &opDecrimentXY,
};

// Shifts right one bit, sets VF to LSB of Vy
const opcode BitShiftRight = {
        .code = 0x8006,
        .function = &opBitShiftRight,
};

// Vx = Vy - Vx
const opcode SubXY = {
        .code = 0x8007,
        .function = &opSubXY
};

const opcode BitShiftLeft = {
        .code = 0x800E,
        .function = &opBitShiftLeft,
};

const opcode SkipIfEqXY = {
        .code = 0x9000,
        .function = &opSkipIfEqXY,
};

const opcode SetAddress = {
        .code = 0xA000,
        .function = &opSetAddress,
};
// Sets PC = V0 + NNN
const opcode SetPCV0 = {
        .code = 0xB000,
        .function = &opSetPCV0,
};

// Vx = Rand(0:255) & NN
const opcode RandAnd = {
        .code = 0xC000,
        .function = &opRandAnd,
};

// Display, draws a sprite at coordinate (Vx, Vy) that is 8 pixels wide and a height
// of N. Each row is bit encoded starting at address I. VF is set to 1 if any screen
// pixels are flipped from set to unset. And remains 0 otherwise.
const opcode Draw = {
        .code = 0xD000,
        .function = &opDraw,
};

// Skips next instruction if Vx Key has been pressed.
const opcode SkipIfPressed = {
        .code = 0xE09E,
        .function = &opSkipIfPressed,
};

// Skips next instruction if Vx Key is not pressed.
const opcode SkipIfnPressed = {
        .code = 0xE0A1,
        .function = &opSkipIfnPressed,
};

// Sets Vx to value of Delay Timer
const opcode SetVTimer = {
        .code = 0xF007,
        .function = &opSetVTimer,
};

// Waits for key then stores in Vx
const opcode WaitForKey = {
        .code = 0xF00A,
        .function = &opWaitForKey,
};
// Sets Delay Timer to Vx
const opcode SetDelayTimer = {
        .code = 0xF015,
        .function = &opSetDelayTimer,
};

const opcode SetSoundTimer = {
        .code = 0xF018,
        .function = &opSetSoundTimer,
};

// Adds Vx to I
const opcode AddIndex = {
        .code = 0xF01E,
        .function = &opAddIndex,
};

// Sets I to loction of sprite for character in Vx.
const opcode SetIndexFont = {
        .code = 0xF029,
        .function = &opSetIndexFont,
};

const opcode StoreBCD = {
        .code = 0xF033,
        .function = &opStoreBCD
};
// Stores V0 to Vx including Vx to Memory I
const opcode MemDump = {
        .code = 0xF055,
        .function = &opMemDump,
};
// Loads V0 to Vx starting at I including Vx
const opcode MemLoad = {
        .code = 0xF065,
        .function = &opMemLoad,
};

const opcode BadOpCode = {
        .code = 0xFFFF,
        .function = &opBadOpCode,
};


// ============================================================================
// ============================================================================
// OPCODE INSTRUCTIONS
// ============================================================================
// ============================================================================


/******************************************************************************
 *
 * 0x0NNN
 * Calls and RCA 1802 program at address NNN. Not necessary for most ROMS
 *
 ******************************************************************************/
void opCall ( Chip8 *chip8 ) {
    return;
}

/******************************************************************************
 *
 * 0x0E0
 * Clears screen
 *
 ******************************************************************************/
void opDisplayClear ( Chip8 *chip8 )
{
    for (int i = 0; i < SCREEN_RESOLUTION; i++) {
        chip8->gfx[i] = 0;
    }

}

/******************************************************************************
 *
 * 0x0EE
 * Returns from a subroutine
 *
 ******************************************************************************/
void opReturn ( Chip8 *chip8 ) {
    if (chip8->SP > 0) {
        chip8->PC = chip8->stack[chip8->SP - 1];
        chip8->SP--;
    }
    else {
        chip8->status_flag |= STACK_UNDERFLOW;
    }
}

/******************************************************************************
 *
 * 0x1NNN
 * Jumps to memory address NNN.
 *
 ******************************************************************************/
void opGoto ( Chip8 *chip8 ) {
    unsigned short address = (chip8->current_opcode & 0x0FFF);
    chip8->PC = address & 0x0FFF;
}

/******************************************************************************
 *
 * 0x2NNN
 * Calls subroutine at NNN.
 *
 ******************************************************************************/
void opCallSubRoutine ( Chip8 *chip8 ) {
    if ( chip8->SP < STACK_SIZE ) {
        chip8->stack[chip8->SP] = (chip8->PC & 0x0FFF);
        chip8->SP++;
    }
    chip8->PC = (chip8->current_opcode & 0x0FFF);
}

/******************************************************************************
 *
 * 0x3XNN
 * Skips next instruction set if Vx == NN
 *
 ******************************************************************************/
void opSkipIfEqN ( Chip8 *chip8 ){
    if (chip8->V[(chip8->current_opcode & 0x0F00) >> 8] == (chip8->current_opcode & 0x00FF) ) {
        chip8->PC+=2;
    }
}

/******************************************************************************
 *
 * 0x4XNN
 * Skips next instruction if Vx != NN
 *
 ******************************************************************************/
void opSkipIfnEqN ( Chip8 *chip8 ) {
    if (chip8->V[(chip8->current_opcode & 0x0F00) >> 8] != (chip8->current_opcode & 0x00FF) ) {
        chip8->PC+=2;
    }
}

/******************************************************************************
 *
 * 0x5XY0
 * Skips next instruction if Vx == Vy
 *
 ******************************************************************************/
void opSkipIfEq ( Chip8 *chip8 ) {
    unsigned short x_index, y_index;
    x_index = (chip8->current_opcode & 0x0F00)>>8;
    y_index = (chip8->current_opcode & 0x00F0)>>4;

    if (chip8->V[x_index] == chip8->V[y_index]) {
        chip8->PC+=2;
    }
}

/******************************************************************************
 *
 * 0x6XNN
 * Sets Vx = NN
 *
 ******************************************************************************/
void opSetRegister ( Chip8 *chip8 ) {

    unsigned char register_value = (chip8->current_opcode & 0x00FF);
    chip8->V[(chip8->current_opcode & 0x0F00)>>8] = register_value & 0x00FF;
}

/******************************************************************************
 *
 * 0x7XNN
 * Sets Vx += NN
 *
 ******************************************************************************/
void opIncrementRegister ( Chip8 *chip8 ) {
    chip8->V[(chip8->current_opcode & 0x0F00) >> 8] += (chip8->current_opcode & 0x00FF);
}

/******************************************************************************
 *
 * 0x8XY0
 * Sets Vx = Vy
 *
 ******************************************************************************/
void opAssignRegister ( Chip8 *chip8 ) {
    chip8->V[(chip8->current_opcode & 0x0F00) >> 8] = chip8->V[(chip8->current_opcode & 0x00F0) >> 4];
}

/******************************************************************************
 *
 * 0x8XY1
 * Sets Vx = Vx | Vy
 *
 ******************************************************************************/
void opBitOr (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (vx | vy) & 0xFF;

}

/******************************************************************************
 *
 * 0x8XY2
 * Sets Vx = Vx & Vy
 *
 ******************************************************************************/
void opBitAnd (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (vx & vy) & 0xFF;

}

/******************************************************************************
 *
 * 0x8XY3
 * Sets Vx = Vx ^ Vy
 *
 ******************************************************************************/
void opBitXor (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (vx ^ vy) & 0xFF;

}

/******************************************************************************
 *
 * 0x8XY4
 * Sets Vx += Vy, sets Vf if carry
 *
 ******************************************************************************/
void opAddXY ( Chip8 *chip8 ) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    if ((vx + vy) > 0xFF){
        chip8->V[0xF] = 1;
    }
    else
        chip8->V[0xf] = 0;

    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (vx + vy) & 0xFF;

}

/******************************************************************************
 *
 * 0x8XY5
 * Sets Vx -= Vy, sets Vf to 0 if borrow
 *
 ******************************************************************************/
void opDecrimentXY ( Chip8 *chip8 ) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    if ((vx - vy) < 1){
        chip8->V[0xF] = 0;
        chip8->V[(chip8->current_opcode&0x0F00)>>8] = -(vx - vy) & 0xFF;
        return;

    }
    chip8->V[0xF] = 1;
    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (vx - vy) & 0xFF;
}

/******************************************************************************
 *
 * 0x8XY6
 * Sets Vx = Vy>>1, sets Vf to LSB of Vy
 *
 ******************************************************************************/
void opBitShiftRight (Chip8 *chip8) {
    chip8->V[0xf] = (chip8->V[((chip8->current_opcode&0x00F0)>>4)] & 0x1);
    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (chip8->V[(chip8->current_opcode&0x00F0)>>4] >> 1) & 0xFF;
}

/******************************************************************************
 *
 * 0x8XY7
 * Sets Vx = Vy - Vx, sets Vf to 0 if borrow, 1 if none.
 *
 ******************************************************************************/
void opSubXY (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)>>8];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)>>4];

    if ((vy - vx) < 1){
        chip8->V[0xF] = 0;
        chip8->V[(chip8->current_opcode&0x0F00)>>8] = -(vy - vx) & 0xFF;
        return;
    }
    chip8->V[0xf] = 1;
    chip8->V[chip8->current_opcode&0x0F00] = (vy - vx) & 0xFF;
}

/******************************************************************************
 *
 * 0x8XYE
 * Sets Vx = Vy << 1. sets Vf to MSB of Vy
 *
 ******************************************************************************/
void opBitShiftLeft (Chip8 *chip8) {
    chip8->V[0xf] = chip8->current_opcode & 0xF;
    chip8->V[(chip8->current_opcode&0x0F00)>>8] = (chip8->V[(chip8->current_opcode&0x00F0)>>4] << 1) & 0xFF;
}

/******************************************************************************
 *
 * 0x9Y0
 * Skips block of code if Vx == Vy
 *
 ******************************************************************************/
void opSkipIfEqXY(Chip8 *chip8) {
    if (chip8->V[(chip8->current_opcode & 0x0F00)] != chip8->V[chip8->current_opcode &0x00F0]) {
        chip8->PC+=2;
    }
}

/******************************************************************************
 *
 * 0xANNN
 * Sets I to memory address NNNN
 *
 ******************************************************************************/
void opSetAddress ( Chip8 *chip8 ) {
    chip8->I = (chip8->current_opcode & 0x0FFF);
}

/******************************************************************************
 *
 * 0xBNNN
 * Sets PC = V0 + NNN
 *
 ******************************************************************************/
void opSetPCV0 (Chip8 *chip8) {
    chip8->PC = (chip8->current_opcode&0x0FFF) + chip8->V[0];
}

/******************************************************************************
 *
 * 0xCXNN
 * Sets Vx = NN & rand(0:255). Uses rand function from stdlib that is seeded
 * with the current time.
 *
 ******************************************************************************/
void opRandAnd ( Chip8 *chip8 ) {
    srand(time(NULL));
    int random_number = rand() & 0xff;
    chip8->V[(chip8->current_opcode & 0x0F00)>>8] = (chip8->current_opcode & 0x00FF) & random_number;
}

/******************************************************************************
 * 0xDXYN
 * Draws a sprite at coordinate (Vx, Vy) that has a width of 8 pixels and a height of N pixels.
 * Pixels are bit encoded starting at memory address I. I is not adjusted after operation and V[f]
 * is set if a pixel is set from 1 to 0
 ******************************************************************************/
void opDraw ( Chip8 *chip8 ) {
    unsigned char num_rows, bit_pixel, x, y;
    num_rows = chip8->current_opcode & 0x000F;
    bit_pixel = chip8->memory[chip8->I];
    x = chip8->V[chip8->current_opcode & 0x0F00 >> 8];
    y = chip8->V[chip8->current_opcode & 0x00F0 >> 4];

    chip8->V[0xf] = 0;
    for (int yline = 0; yline < num_rows; yline++) {
        bit_pixel = chip8->memory[chip8->I + yline];
        for (int xline = 0; xline < 8; xline++) {
            if((bit_pixel & (0x80 >> xline)) != 0){
                if(chip8->gfx[(x+xline + ((y+yline)*64 ))] == 1 )
                    chip8->V[0xf] = 1;

                chip8->gfx[x + xline + ((y + yline)*64)] ^= 1;
            }
        }
    chip8->draw_flag = 1;
    }

}

/******************************************************************************
 *
 * 0xEX9E
 * Skips next instruction set if key[Vx] == pressed
 *
 ******************************************************************************/
void opSkipIfPressed (Chip8 *chip8) {
    if( chip8->key_state[(chip8->current_opcode&0x0F00)>>8] == 1){
        chip8->PC +=2;
    }
}

/******************************************************************************
 *
 * 0xEXA1
 * Skips next instruction if key_state[Vx] != pressed
 *
 ******************************************************************************/
void opSkipIfnPressed (Chip8 *chip8) {
    if( chip8->key_state[(chip8->current_opcode&0x0F00)>>8] != 1){
        chip8->PC +=2;
    }
}

/******************************************************************************
 *
 * 0xFX07
 * sets Vx to value of delay timer
 *
 ******************************************************************************/
void opSetVTimer(Chip8 *chip8) {
    chip8->V[(chip8->current_opcode & 0x0F00)>>8] = (chip8->delay_timer) & 0xff;
}

/******************************************************************************
 *
 * 0xFX0A
 * Waits for key press specified by Vx. This is a blocking operation. All
 * Instructions are halted.
 *
 ******************************************************************************/
void opWaitForKey(Chip8 *chip8) {
    unsigned char key_val = (chip8->current_opcode & 0x0F00) >> 8;
    while(chip8->key_state[key_val] != 1);
}

/******************************************************************************
 *
 * 0xFX15
 * Sets delay timer to Vx
 *
 ******************************************************************************/
void opSetDelayTimer (Chip8 *chip8) {
    chip8->delay_timer = (chip8->V[(chip8->current_opcode & 0x0F00)>>8]);
}

/******************************************************************************
 *
 * 0xFX18
 * Sets sound timer to Vx
 *
 ******************************************************************************/
void opSetSoundTimer(Chip8 *chip8) {
    chip8->sound_timer = (chip8->V[(chip8->current_opcode & 0x0F00)>>8]);
}

/******************************************************************************
 *
 * 0xFX1E
 * Increments I by Vx
 *
 ******************************************************************************/
void opAddIndex (Chip8 *chip8) {
    chip8->I += (chip8->V[(chip8->current_opcode&0x0F00)>>8]);
}

/******************************************************************************
 *
 * 0xFX29
 * Sets I to the proper font character stored in Vx.
 *
 ******************************************************************************/
void opSetIndexFont (Chip8 *chip8) {

}

/******************************************************************************
 *
 * 0xFX33
 * Store the binary coded decimal representation of VX. With the 3 most
 * significant digits stored in memory address I, middle digits in I+1 and
 * last 3 digits in I+2
 * memory[I] = Vx / 100
 * memory[I+1] = (Vx / 10) % 10
 * memory[I+2] = (Vx % 100) % 10
 *
 ******************************************************************************/
void opStoreBCD(Chip8 *chip8) {
    chip8->memory[chip8->I] = chip8->V[(chip8->current_opcode & 0x0F00)>>8] / 100;
    chip8->memory[chip8->I + 1] = (chip8->V[(chip8->current_opcode & 0x0F00)>>8] / 10) % 10;
    chip8->memory[chip8->I + 2] = (chip8->V[(chip8->current_opcode & 0x0F00)>>8] % 100) % 10;
}

/******************************************************************************
 *
 * 0xFX55
 * Stores V0 through VX in memory address I, I is incremineted for each value written
 *
 ******************************************************************************/
void opMemDump(Chip8 *chip8) {
    int count = (chip8->current_opcode & 0x0F00) >> 8;
    for (int i = 0; i <= count; i++) {
        if(chip8->I < 0x1000) {
            chip8->memory[chip8->I] = chip8->V[i];
            chip8->I++;
        }
    }
}

/******************************************************************************
 *
 * 0xFX65
 * Fills V0 to Vx including Vx starting at memory address I
 *
 ******************************************************************************/
void opMemLoad(Chip8 *chip8) {
    int count = (chip8->current_opcode & 0x0F00) >> 8;
    for (int i = 0; i <= count; i++) {
        if(chip8->I < 0x1000) {
            chip8->V[i] = chip8->memory[chip8->I];
            chip8->I++;
        }
    }
}

/******************************************************************************
 *
 * -------- NOT YET IMPLEMENTED ----------
 * Bad opcode. If the opcode being decoded does not match any of the known
 * opcodes, this function is called.
 *
 ******************************************************************************/
void opBadOpCode (Chip8 *chip8) {
    return;
}

const opcode CHIP8_OPCODES[MAX_OPCODES] = {

        Call, DisplayClear, Return, Goto, CallSubRoutine, SkipIfEqN,
        SkipIfnEqN, SkipIfEq, SetRegister, IncrementRegister, AssignRegister,
        BitOr, BitAnd, BitXor, AddXY, DecrimentXY, BitShiftRight, SubXY,
        BitShiftLeft, SkipIfEqXY, SetAddress, SetPCV0, RandAnd, Draw, SkipIfPressed,
        SkipIfnPressed, SetVTimer, WaitForKey, SetDelayTimer, SetSoundTimer, AddIndex,
        SetIndexFont, StoreBCD, MemDump, MemLoad, BadOpCode,

};

