#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "bus.h"
#include "timers.h"
#include "cpu.h"
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
	CARTRIDGE* cartridge;

	void request_timer_interrupt();
	bool timer_interrupt_requested;
};