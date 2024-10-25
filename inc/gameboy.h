#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <SDL.h>

#include "bus.h"
#include "timers.h"
#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"


class GAMEBOY
{
public:
	GAMEBOY(std::string rom_path);
	void run_emulation();
private: 

	BUS*       bus;
	CPU*       cpu;
	TIMERS     timers;
	PPU*       ppu;
	CARTRIDGE* cartridge;

	void request_timer_interrupt();
	bool timer_interrupt_requested;

	std::chrono::high_resolution_clock::time_point last_frame_time;
	uint8_t elapsed_t_cycles;

	void init_window();
	SDL_Window* window;
	SDL_Surface* window_surface;
};