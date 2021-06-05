//NES Emulator written in C++
//
//
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"
using namespace std;

#define MEMORY_SIZE  0x10000

std::string registers_name[] = {
    "A  ", "X  ", "Y  ", "S  "
};

static Emulator* create_emu(size_t memsize, uint16_t pc){
    Emulator* emu = (Emulator*) malloc(sizeof(Emulator));
    //RAMを確保
    emu->memory = (uint8_t*) malloc(memsize);
    //レジスタを初期化
    memset(emu->reg, 0, sizeof(emu->reg));
    emu->pc = pc;
    emu->reg[S] = 0xfd;
    set_flag(emu, IRQ, true);
    set_flag(emu, BREAK, true);
    set_flag(emu, RESERVED, true);

    return emu;
}

static void destroy_emu(Emulator* emu){
    free(emu->memory);
    free(emu);
}

static void dump_registers(Emulator* emu){
    cout << "-------- registers --------" << endl;
    cout << (hex) << "PC : 0x" << (unsigned int)emu->pc << endl;
    for(int i = 0; i < REGISTERS_COUNT; ++i){
        cout << (hex) << registers_name[i] << ": 0x" << (unsigned int)emu->reg[i] << endl;
    }
    
}

static void dump_memory(Emulator* emu, int addr, int size){
    addr -= addr % 16;
    cout << "-------- memory --------" << endl;
    printf("       |00 01 02 03  04 05 06 07  08 09 0a 0b  0c 0d 0e 0f \n");
    printf("-------+---------------------------------------------------\n");
    for(int i = addr; i < addr + size; ++i){
        if(i % 16 == 0) printf("0x%04x |", i);
        printf("%02x ",emu->memory[i]);
        if(i % 4 == 3) printf("|");
        if(i % 16 == 15) printf("\n");
    }
}


int main(int argc, char* argv[]){

    FILE* binary;
    Emulator* emu;

    uint8_t* rom;
    uint8_t* ChrRom;
    int PrgRomSize, ChrRomSize;

    if(argc != 2){
        cout << "usage: main [filename]" << endl;
        return 1;
    }

    //create emulator, pc = 0x8000, s = 0xfd
    cout << "Creating emulator..." << endl;
    emu = create_emu(MEMORY_SIZE, 0x8000);

    cout << "Loading binary..." << endl;
    binary = fopen(argv[1], "rb");
    if(binary == NULL){
        cout << "Cannot open file: " << argv[1] << endl;
        return 1;
    }
    //load binary to memory by 0x10000 bytes
    rom = (uint8_t*) malloc(0x10000);
    ChrRom = (uint8_t*) malloc(0x10000);

    fread(rom, 1, 0x4000, binary);
    fclose(binary);

    //NESヘッダーを解析して,プログラムROMとキャラクターROMに分割する
    PrgRomSize = (unsigned int) rom[4] * 16 * 1024;
    ChrRomSize = (unsigned int) rom[5] *  8 * 1024;

    cout << (hex) << "Program ROM size = " << PrgRomSize << " byte" << endl;
    cout << (hex) << "Program ROM size = " << PrgRomSize << " byte" << endl;

    //16b header, PrgRomSize byte Prg, ChrRomSize byte Chr
    memcpy(emu->memory + 0x8000, rom + 0x10, PrgRomSize);
    memcpy(ChrRom, rom + 0x10 + PrgRomSize, ChrRomSize);

    free(rom);


    init_instructions();

    while((uint32_t) emu->pc < MEMORY_SIZE){
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

