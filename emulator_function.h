#ifndef EMULATOR_FUNCTION_H_
#define EMULATOR_FUNCTION_H_

#include <stdint.h>

#include "emulator.h"

uint8_t get_code8(Emulator* emu, int index);

int8_t get_sign_code8(Emulator* emu, int index);

#endif