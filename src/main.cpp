#include "gameboy.h"
#include <SDL.h>

int main(int argc, char** args)
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/01-special.gb"); 
    gameboy.run_emulation();
    return 0;
}