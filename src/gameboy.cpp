#include "gameboy.h"

GAMEBOY::GAMEBOY(std::string rom_path)
{
    joypad = JOYPAD();
    cartridge = new CARTRIDGE(rom_path);
    timers = TIMERS();
    ppu = new PPU();
    bus = new BUS(cartridge, &timers, ppu, &joypad);
    cpu = new CPU(bus);

    interrupts = false;
}

void GAMEBOY::run_emulation()
{
	while (true)
    {
        elapsed_t_cycles = cpu->tick();
        interrupts |= timers.tick(elapsed_t_cycles);
        interrupts |= ppu->tick(elapsed_t_cycles);
        interrupts |= joypad.read_input();
        request_interrupts();
    }
}

void GAMEBOY::request_interrupts()
{
    if (interrupts & REQUEST_TIMER_INTERRUPT)
    {
        add_interrupt(IF_TIMER_MASK);
        bus->write_memory(TIMA, bus->read_memory(TMA));
    }
    if (interrupts & REQUEST_VBLANK_INTERRUPT)
    {
        add_interrupt(IF_VBLANK_MASK);
    }
    if (interrupts & REQUEST_LCD_INTERRUPT)
    {
        add_interrupt(IF_LCD_MASK);
    }
    if (interrupts & REQUEST_JOYPAD_INTERRUPT)
    {
        add_interrupt(IF_JOYPAD_MASK);
    }
    interrupts = 0;
}

void GAMEBOY::add_interrupt(uint8_t interrupt_type)
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | interrupt_type);
}