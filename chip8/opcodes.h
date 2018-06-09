

#ifndef CHIP8_OPCODES_H
#define CHIP8_OPCODES_H

#define MAX_OPCODES 35
typedef struct opcode {
    unsigned short code;
    void *function;
}opcode;

#endif //CHIP8_OPCODES_H
