#include "gameboy.h"
#include <SDL.h>

int main(int argc, char** args)
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/11-op a,(hl).gb");
    gameboy.run_emulation();
    return 0;
}