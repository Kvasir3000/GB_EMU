#include "bus.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = 0x26;
	ram[0x101] = 0x10;
	ram[0x102] = 0x2E;
	ram[0x103] = 0x00;
	ram[0x1000] = 0x23; 
	ram[0x104] = 0x3A;
 };

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};