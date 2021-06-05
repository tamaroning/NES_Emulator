#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"
using namespace std;

// Update Status registers by each bit
//
//
void update_negative(Emulator* emu, uint8_t val){
    if(val & 1<<7)emu->flag[NEGATIVE] = true;
    else emu->flag[NEGATIVE] = false;
}

void update_zero(Emulator* emu, uint8_t val){
    if(val == 0) emu->flag[ZERO] = true;
    else emu->flag[ZERO] = false;
}

// Update status registers
//

//tsx tsa txs ...
void update_flag_t(Emulator* emu, uint8_t val){
    update_zero(emu, val);
    update_negative(emu, val);
}

//ldx ldy ...
void update_flag_ld(Emulator* emu, uint8_t val){
    update_zero(emu, val);
    update_negative(emu, val);
}

//0x78 sei 1byte
//IRQ割り込みを禁止する
void sei(Emulator* emu){
    //IRQ割り込みを禁止
    set_flag(emu, IRQ, true);
    emu->pc += 1;
}

//0xba tsx 1byte
//copy s to x
void tsx(Emulator* emu){
    emu->reg[X] = emu->reg[S];
    
    update_flag_t(emu, emu->reg[S]);
    emu-> pc += 1;
}

//0x9a txs 1byte
//copy x to s
void txs(Emulator* emu){
    emu->reg[S] = emu->reg[X];
    
    update_flag_t(emu, emu->reg[X]);
    emu-> pc += 1;
}

//0x8d lda abs 3byte


//0xa9 lda_imm 2byte
void lda_imm(Emulator* emu){
    uint8_t imm = get_code8(emu,1);
    emu->reg[A] = imm;

    update_flag_ld(emu,imm);
    emu->pc += 2;
}

//0xa2 ldx_imm 2byte
void ldx_imm(Emulator* emu){
    uint8_t imm = get_code8(emu,1);
    emu->reg[X] = imm;

    update_flag_ld(emu,imm);
    emu->pc += 2;
}

//0xa0 ldy_imm 2byte
void ldy_imm(Emulator* emu){
    uint8_t imm = get_code8(emu,1);
    emu->reg[Y] = imm;

    update_flag_ld(emu,imm);
    emu->pc += 2;
}


//オペコードと関数の紐付け

instruction_func_t* instructions[256];

void init_instructions(void){
    memset(instructions, 0, sizeof(instructions));
    instructions[0x78] = sei;
    instructions[0x9a] = txs;
    instructions[0xa2] = ldx_imm;
    instructions[0xa9] = lda_imm;
    
}
