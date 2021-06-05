#include "emulator_function.h"

uint8_t get_code8(Emulator* emu, int index) {
    return emu->memory[emu->pc + index];
}

int8_t get_sign_code8(Emulator* emu, int index) {
    return (int8_t)emu->memory[emu->pc + index];
}

//ステータスレジスタのセット
void set_flag(Emulator* emu, int REG_NUM, bool value){
    emu->flag[REG_NUM] = value;
}

bool get_flag(Emulator* emu, int REG_NUM){
    return emu->flag[REG_NUM];
}


