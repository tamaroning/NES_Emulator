#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"
using namespace std;

//sei 1byte
//割り込みを禁止する
void sei(Emulator* emu){
    //IRQ割り込みを禁止
    cout << "sei" << endl;
    emu->pc += 1;
}

//ldx_imm 2byte
void ldx_imm(Emulator* emu){
    uint8_t imm = get_code8(emu,1);
    emu->reg[X] = imm;

    emu->pc += 2;
}

//オペコードと関数の紐付け

instruction_func_t* instructions[256];

void init_instructions(void){
    memset(instructions, 0, sizeof(instructions));
    instructions[0x78] = sei;
    instructions[0xa2] = ldx_imm;
    
}
