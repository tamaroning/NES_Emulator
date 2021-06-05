#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <string>

enum Register {
    A, X, Y, S, REGISTERS_COUNT,
};

//IRQ 0:IRQ許可 1:IRQ禁止 RESERVED 常に1
enum Stat {
    CARRY, ZERO, IRQ, DECIMAL, BREAK, RESERVED, OVERFLOW, NEGATIVE, 
};

typedef struct {
    //A, X, Y, S, P registers
    uint8_t reg[REGISTERS_COUNT];
    
    //status register, or P
    bool flag[8];

    //PC register
    uint16_t pc;

    uint8_t* memory;
} Emulator;


#endif