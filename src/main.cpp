#include "gameboy.h"

int main()
{
    GAMEBOY gameboy("../tests/cpu/Blarggs/11-op a,(hl).gb");
    gameboy.run_emulation();
    return 0;
}