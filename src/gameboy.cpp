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
        request_interrupts();
        joypad.read_input();
    }
}

void GAMEBOY::request_interrupts()
{
    if (interrupts & REQUEST_TIMER_INTERRUPT)
    {
        request_timer_interrupt();
    }
    if (interrupts & REQUEST_VBLANK_INTERRUPT)
    {
        request_vblank_interrupt();
    }
    if (interrupts & REQUEST_LCD_INTERRUPT)
    {
       // request_lcd_interrupt();
    }
    interrupts = 0;
}

void GAMEBOY::request_timer_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
    bus->write_memory(TIMA, bus->read_memory(TMA)); 
}

void GAMEBOY::request_vblank_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_VBLANK_MASK);
}

void GAMEBOY::request_lcd_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_LCD_MASK);
}