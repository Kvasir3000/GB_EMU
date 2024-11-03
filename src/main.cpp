#include "gameboy.h"
#include <SDL.h>

int main(int argc, char** args)
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/Tetris (JUE) (V1.1) [!].gb"); 
    gameboy.run_emulation();
    return 0;
}