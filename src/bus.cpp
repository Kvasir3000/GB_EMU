#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"
#include <iostream>

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	uint8_t col = 0;
	uint8_t row = 0;
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};