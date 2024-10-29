#include "gameboy.h"
#include <SDL.h>

int main(int argc, char** args)
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/cpu_instrs.gb"); 
    gameboy.run_emulation();
    return 0;
}