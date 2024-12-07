#include "gameboy.h"
#include <SDL.h>

int main(int argc, char** args)
{
    GAMEBOY gameboy; 
    gameboy.run_emulation();
    return 0;
}