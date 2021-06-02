#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <string>

enum Register {
    A, X, Y, SP, REGISTERS_COUNT,
};

typedef struct {
    //A, X, Y, S, P registers
    uint8_t reg[REGISTERS_COUNT];
    
    //status register, or P
    uint8_t flags;

    //PC register
    uint16_t pc;

    uint8_t* memory;
} Emulator;

#endif