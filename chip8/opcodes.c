
#include "opcodes.h"
#include "opcode_functions.h"

opcode Call = {
        .code = 0x000,
        .function = &oCall,
};
opcode Display = {
        .code = 0x000,
        .function = &oDisplay,
};




opcode CHIP8_OPCODES[MAX_OPCODES] = {
        Call,
        Display,

};
