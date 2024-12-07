#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <SDL.h>
#include <thread>
#if defined WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

#include "bus.h"
#include "timers.h"
#include "cpu.h"
#include "ppu.h"
#include "joypad.h"
#include "cartridge.h"


class GAMEBOY
{
public:
	GAMEBOY();
	void run_emulation();
private: 

	bool       run_emulator;

	BUS*       bus;
	CPU*       cpu;
	TIMERS     timers;
    PPU*       ppu;
	JOYPAD     joypad;
	CARTRIDGE* cartridge;

	std::string rom_path;
	void get_rom_file();

	void request_interrupts();
	void add_interrupt(uint8_t interrupt_type);
	void request_timer_interrupt();
	void request_vblank_interrupt();
	void request_lcd_interrupt();
	void request_joypad_interrupt();
	uint8_t interrupts;

	uint8_t elapsed_t_cycles;
};