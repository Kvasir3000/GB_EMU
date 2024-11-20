#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "common/memory_map_defs.h"
#include "common/mbc1_defs.h"


class CARTRIDGE
{
public:
	CARTRIDGE();
	CARTRIDGE(std::string rom_path);
	CARTRIDGE(std::string rom_path, std::vector<uint8_t> program_data);
	uint8_t read_rom_bank_nn(uint16_t memory_address);
	uint8_t read_rom_bank0(uint16_t memory_address);
	void    write_rom(uint16_t memory_address, uint8_t data);
	uint8_t read_ram(uint16_t memory_address);
	void    write_ram(uint16_t memory_address, uint8_t data);

private:
	uint8_t rom_bank_idx;
	uint8_t ram_bank_idx;
	bool    ram_enable;
 	std::vector<uint8_t> program_data;
	std::vector<std::vector<uint8_t>> rom_banks;
	std::vector<std::vector<uint8_t>> ram_banks;
	void read_program(std::string rom_path);

	void init_memory_banks(std::vector<std::vector<uint8_t>>&memory_bank, uint8_t number_of_banks, uint16_t bank_size);
	void fill_rom();
};