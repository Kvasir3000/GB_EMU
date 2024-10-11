#include "gameboy.h"

GAMEBOY::GAMEBOY(std::string rom_path)
{
    std::vector<uint8_t> program_data;
    cartridge = new CARTRIDGE(rom_path);
    timers = TIMERS();
    bus = new BUS(cartridge, &timers);
    cpu = new CPU(bus);
    timer_interrupt_requested = false;
}

void GAMEBOY::run_emulation()
{
	while (true)
    {
        uint8_t elapsed_t_cycles = cpu->tick();
        timer_interrupt_requested = timers.tick(elapsed_t_cycles);
        if (timer_interrupt_requested)
        {
            request_timer_interrupt();
        }
	}
}

void GAMEBOY::request_timer_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
    bus->write_memory(TIMA, bus->read_memory(TMA)); 
    timer_interrupt_requested = false;
}