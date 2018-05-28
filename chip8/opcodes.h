//
// Created by Zach Campbell on 5/28/18.
//

#ifndef CHIP8_OPCODES_H
#define CHIP8_OPCODES_H

typedef struct opcode {
    unsigned short code;
    void *function;
}opcode;

#endif //CHIP8_OPCODES_H
