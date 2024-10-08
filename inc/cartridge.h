#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "common/memory_map_defs.h"


class CARTRIDGE
{
public:
	CARTRIDGE();
	CARTRIDGE(std::string rom_path);
	uint8_t read_rom(uint16_t memory_address);
	void    write();
	uint8_t read_ram(uint16_t memory_address);

private:
	uint8_t rom_bank_idx;
	uint8_t ram_bank_idx;
 	std::vector<uint8_t> program_data;
	std::vector<std::vector<uint8_t>> ram_banks;
	void read_program(std::string rom_path);
};