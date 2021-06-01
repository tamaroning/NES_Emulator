//NES Emulator
//
//
// short is 2byte
#include <iostream>
#include <stdint.h>

enum Register {
    A, X, Y, S, P, REGISTERS_COUNT,
};

typedef struct {
    //A, X, Y, S, P registers
    uint8_t reg[REGISTERS_COUNT];
    
    //status register
    uint8_t flags;

    //PC register
    uint16_t pc;

    uint8_t* memory;
} Emulator;

Emulator* create_emu(size_t memsize, uint16_t pc, uint8_t s){
    Emulator* emu = malloc(sizeof(Emulator));
    emu->memory = malloc(memsize);

    memset(emu->reg, 0, sizeof(emu->reg));
    emu->pc = pc;
    emu->reg[S] = s;

    return emu;
}

void destroy_emu(Emulator* emu){
    free(emu->memory);
    free(emu);
}

int main(int argc, char* argv[]){

    FILE* binary;
    Emulator* emu;

    if(argc != 2){
        cout << "usage: emu [filename]" << endl;
        return 1;
    }

    emu = create_emu(MEMORY_SIZE, 0x0000, 0x00);

    binary = fopen(argv[1], "rb");
    if(binary == NULL){
        cout << "cannot open file: " << argv[1] << endl;
        return 1;
    }

    //load binary to memory
    fread(emnu->memory, 1, 0x200, binary);
    fclose(binary);

    destroy_emu(emu);

    return 0;
}

