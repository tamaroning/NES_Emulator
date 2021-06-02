//NES Emulator written in C++
//
//
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"
using namespace std;

#define MEMORY_SIZE  (2 * 1024)

std::string registers_name[] = {
    "A  ", "X  ", "Y  ", "SP "
};

static Emulator* create_emu(size_t memsize, uint16_t pc, uint8_t sp){
    Emulator* emu = (Emulator*) malloc(sizeof(Emulator));
    emu->memory = (uint8_t*) malloc(memsize);

    memset(emu->reg, 0, sizeof(emu->reg));
    emu->pc = pc;
    emu->reg[SP] = sp;

    return emu;
}

static void destroy_emu(Emulator* emu){
    free(emu->memory);
    free(emu);
}

static void dump_registers(Emulator* emu){
    cout << "----- registers -----" << endl;
    cout << (hex) << "PC : 0x" << (unsigned int)emu->pc << endl;
    for(int i = 0; i < REGISTERS_COUNT; ++i){
        cout << (hex) << registers_name[i] << ": 0x" << (unsigned int)emu->reg[i] << endl;
    }
    cout << (hex) << "FLG: 0x" << (unsigned int)emu->flags << endl;
    
}



int main(int argc, char* argv[]){

    FILE* binary;
    Emulator* emu;

    if(argc != 2){
        cout << "usage: main [filename]" << endl;
        return 1;
    }

    //create emulator, pc = 0x0010, s = 0x00
    cout << "Creating emulator..." << endl;
    emu = create_emu(MEMORY_SIZE, 0x0010, 0x00);

    cout << "Loading binary..." << endl;
    binary = fopen(argv[1], "rb");
    if(binary == NULL){
        cout << "Cannot open file: " << argv[1] << endl;
        return 1;
    }
    //load binary to memory by 512 bytes
    fread(emu->memory, 1, 0x200, binary);
    fclose(binary);
    cout << "Successful!" << endl;

    init_instructions();

    while(emu->pc < MEMORY_SIZE){
        uint8_t opecode = get_code8(emu, 0);
        if(instructions[opecode] == NULL){
            cout << (hex) << "Not implemented: opecode = 0x" << (unsigned int)opecode << endl;
            break;
        }
        instructions[opecode](emu);

    }

    dump_registers(emu);

    cout << "Exiting..." << endl;
    destroy_emu(emu);

    return 0;
}

