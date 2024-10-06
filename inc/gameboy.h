#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "bus.h"
#include "timers.h"
#include "cpu.h"


class GAMEBOY
{
public:
	GAMEBOY(std::string rom_path);
	void run_emulation();
private: 

	BUS*    bus;
	CPU*     cpu;
	TIMERS timers;

	void read_program(std::vector<uint8_t>& program_data, std::string rom_path);
	 
};