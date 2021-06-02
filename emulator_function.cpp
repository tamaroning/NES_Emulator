#include "emulator_function.h"

uint8_t get_code8(Emulator* emu, int index) {
    return emu->memory[emu->pc + index];
}

int8_t get_sign_code8(Emulator* emu, int index) {
    return (int8_t)emu->memory[emu->pc + index];
}

