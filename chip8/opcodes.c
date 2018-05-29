
#include "opcodes.h"
#include "opcode_functions.h"

opcode Call = {
        .code = 0x000,
        .function = &oCall,
};

opcode Display = {
        .code = 0x00E0,
        .function = &oDisplay,
};

opcode Return = {
        .code = 0x00EE,
        .function = &oReturn,
};

opcode Goto = {
        .code = 0x1000,
        .function = &oGoto,
};

opcode CallSubRoutine = {
        .code = 0x2000,
        .function = &oCallSubRoutine,
};

// Conditional Subroutines

opcode SkipIfEqN = {
        .code = 0x3000,
        .function = &oSkipIfEqN,
};

opcode SkipIfnEqN = {
        .code = 0x4000,
        .function = &oSkipIfnEqN,
};

opcode SkipIfEq = {
        .code = 0x5000,
        .function = &oSkipIfEq,
};

// Assignment opcodes

opcode SetRegister = {
        .code = 0x6000,
        .function = &oSetRegister,
};

opcode IncrementRegister = {
        .code = 0x7000,
        .function = &oIncrementRegister,
};

opcode AssignRegister = {
        .code = 0x8000,
        .function = &oAssignRegister,
};

// Bitwise Operations

opcode BitOr = {
        .code = 0x8001,
        .function = &oBitOr,
};

opcode BitAnd = {
        .code = 0x8002,
        .function = &oBitAnd,
};

opcode BitXor = {
        .code = 0x8003,
        .function = &oBitXor,
};

// Arithmetic Operators

opcode AddXY = {
        .code = 0x8004,
        .function = &oAddXY,
};
//
opcode DecrimentXY = {
        .code = 0x8005,
        .function = &oDecrimentXY,
};

// Shifts right one bit, sets VF to LSB of Vy
opcode BitShiftRight = {
        .code = 0x8006,
        .function = &oBitshiftRight,
};

// Vx = Vy - Vx
opcode SubXY = {
        .code = 0x8007,
        .function = &oSubXY
};

opcode BitShiftLeft = {
        .code = 0x800E,
        .function = &oBitShiftLeft,
};

opcode SkipIfEqXY = {
        .code = 0x9000,
        .function = &oSkipIfEqXY,
};

opcode SetAddress = {
        .code = 0xA000,
        .function = &oSetAddress,
};
// Sets PC = V0 + NNN
opcode SetPCV0 = {
        .code = 0xB000,
        .function = &oSetPCV0,
};

// Vx = Rand(0:255) & NN
opcode RandAnd = {
        .code = 0xC000,
        .function = &oRandAnd,
};

// Display, draws a sprite at coordinate (Vx, Vy) that is 8 pixels wide and a height
// of N. Each row is bit encoded starting at address I. VF is set to 1 if any screen
// pixels are flipped from set to unset. And remains 0 otherwise.
opcode Draw = {
        .code = 0xD000,
        .function = &oDraw,
};

// Skips next instruction if Vx Key has been pressed.
opcode SkipIfPressed = {
        .code = 0xE09E,
        .function = &oSkipIfPressed,
};











opcode CHIP8_OPCODES[MAX_OPCODES] = {
        Call,
        Display,

};














































