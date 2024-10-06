#include "gameboy.h"

int main()
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/01-special.gb");
    gameboy.run_emulation();
    return 0;
}