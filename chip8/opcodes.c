
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

const opcode StoreBinary = {
        .code = 0xF033,
        .function = &opStoreBinary
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



void opBadOpCode ( void ) {

}

void opCall ( Chip8 *chip8 ) {

}

void opDisplayClear ( Chip8 *chip8 )
{

}
// Returns from a subroutine
void opReturn ( Chip8 *chip8 ) {
    if (chip8->SP > 0) {
        chip8->PC = chip8->stack[SP - 1];
        chip8->SP--;
    }
    else {
        chip8->status_flag |= STACKUNDERFLOW;
    }
}

void opGoto ( Chip8 *chip8 ) {
    unsigned short address = chip8->current_opcode & 0x0FFF;
    chip8->PC = address & 0x0FFF;
}

void opCallSubRoutine ( Chip8 *chip8 ) {
    if ( SP < STACK_SIZE ) {
        chip8->stack[SP] = (chip8->PC & 0x0FFF);
        chip8->SP++;
    }
    chip8->PC = (chip8->current_opcode & 0x0FFF);
}

void opSkipIfEqN ( Chip8 *chip8 ){
    if (chip8->V[chip8->current_opcode & 0x0F00] == (chip8->current_opcode & 0x0FF0) ) {
        chip8->PC+=2;
    }
}

void opSkipIfnEqN ( Chip8 *chip8 ) {
    if (chip8->V[chip8->current_opcode & 0x0F00] != (chip8->current_opcode & 0x0FF0) ) {
        chip8->PC+=2;
    }

}

void opSkipIfEq ( Chip8 *chip8 ) {
    unsigned short x_index, y_index;
    x_index = (chip8->current_opcode & 0x0F00);
    y_index = (chip8->current_opcode & 0x00F0);

    if (chip8->V[x_index] == chip8->V[y_index]) {
        chip8->PC+=2;
    }
}

void opSetRegister ( Chip8 *chip8 ) {

    unsigned char register_value = (chip8->current_opcode & 0x00FF);
    chip8->V[chip8->current_opcode & 0x0F00] = register_value & 0x00FF;
}

void opIncrementRegister ( Chip8 *chip8 ) {
    chip8->V[chip8->current_opcode & 0x0F00] += (chip8->current_opcode & 0x00FF);
}

void opAssignRegister ( Chip8 *chip8 ) {
    chip8->V[(chip8->current_opcode & 0x0F00)] = chip8->V[(chip8->current_opcode & 0x00F0)];
}

void opBitOr (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    chip8->V[chip8->current_opcode&0x0F00] = (vx | vy) & 0xFF;

}

void opBitAnd (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    chip8->V[chip8->current_opcode&0x0F00] = (vx & vy) & 0xFF;

}

void opBitXor (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    chip8->V[chip8->current_opcode&0x0F00] = (vx ^ vy) & 0xFF;

}

void opAddXY ( Chip8 *chip8 ) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    if ((vx + vy) > 0xFF){
        chip8->V[0xF] = 1;
    }
    chip8->V[chip8->current_opcode&0x0F00] = (vx + vy) & 0xFF;

}

void opDecrimentXY ( Chip8 *chip8 ) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    if ((vx - vy) < 1){
        chip8->V[0xF] = 1;
        chip8->V[chip8->current_opcode&0x0F00] = -(vx - vy) & 0xFF;
        return;

    }
    chip8->V[chip8->current_opcode&0x0F00] = (vx - vy) & 0xFF;

}

void opBitShiftRight (Chip8 *chip8) {
    chip8->V[(chip8->current_opcode&0x0F00)] = (chip8->V[(chip8->current_opcode&0x00F0)] >> 1) & 0xFF;
}

void opSubXY (Chip8 *chip8) {
    unsigned char vx = chip8->V[(chip8->current_opcode & 0x0F00)];
    unsigned char vy = chip8->V[(chip8->current_opcode & 0x00F0)];

    if ((vy - vx) < 1){
        chip8->V[0xF] = 1;
        chip8->V[chip8->current_opcode&0x0F00] = -(vy - vx) & 0xFF;
        return;

    }
    chip8->V[chip8->current_opcode&0x0F00] = (vy - vx) & 0xFF;

}

void opBitShiftLeft (Chip8 *chip8) {
    chip8->V[(chip8->current_opcode&0x0F00)] = (chip8->V[(chip8->current_opcode&0x00F0)] >> 1) & 0xFF;
}








const opcode CHIP8_OPCODES[MAX_OPCODES] = {

        Call, DisplayClear, Return, Goto, CallSubRoutine, SkipIfEqN,
        SkipIfnEqN, SkipIfEq, SetRegister, IncrementRegister, AssignRegister,
        BitOr, BitAnd, BitXor, AddXY, DecrimentXY, BitShiftRight, SubXY,
        BitShiftLeft, SkipIfEqXY, SetAddress, SetPCV0, RandAnd, Draw, SkipIfPressed,
        SkipIfnPressed, SetVTimer, WaitForKey, SetDelayTimer, SetSoundTimer, AddIndex,
        SetIndexFont, StoreBinary, MemDump, MemLoad, BadOpCode,

};





