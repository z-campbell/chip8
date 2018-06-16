

#ifndef CHIP8_OPCODES_H
#define CHIP8_OPCODES_H

#define MAX_OPCODES 35

#include "chip8.h"

const typedef struct opcode {
    const unsigned short code;
    const void *function;
} opcode;

extern opcode *CHIP8_OPCODES[MAX_OPCODES + 1];

void opCall(Chip8 *chip8);

void opDisplayClear(Chip8 *chip8);

void opReturn(Chip8 *chip8);

void opGoto(Chip8 *chip8);

void opCallSubRoutine(Chip8 *chip8);

void opSkipIfEqN(Chip8 *chip8);

void opSkipIfnEqN(Chip8 *chip8);

void opSkipIfEq(Chip8 *chip8);

void opSetRegister(Chip8 *chip8);

void opIncrementRegister(Chip8 *chip8);

void opAssignRegister(Chip8 *chip8);

void opBitOr(Chip8 *chip8);

void opBitAnd(Chip8 *chip8);

void opBitXor(Chip8 *chip8);

void opAddXY(Chip8 *chip8);

void opDecrimentXY(Chip8 *chip8);

void opBitShiftRight(Chip8 *chip8);

void opSubXY(Chip8 *chip8);

void opBitShiftLeft(Chip8 *chip8);

void opSkipIfEqXY(Chip8 *chip8);

void opSetAddress(Chip8 *chip8);

void opSetPCV0(Chip8 *chip8);

void opRandAnd(Chip8 *chip8);

void opDraw(Chip8 *chip8);

void opSkipIfPressed(Chip8 *chip8);

void opSkipIfnPressed(Chip8 *chip8);

void opSetVTimer(Chip8 *chip8);

void opWaitForKey(Chip8 *chip8);

void opSetDelayTimer(Chip8 *chip8);

void opSetSoundTimer(Chip8 *chip8);

void opAddIndex(Chip8 *chip8);

void opSetIndexFont(Chip8 *chip8);

void opStoreBCD(Chip8 *chip8);

void opMemDump(Chip8 *chip8);

void opMemLoad(Chip8 *chip8);

void opBadOpCode(Chip8 *chip8);

#endif //CHIP8_OPCODES_H
