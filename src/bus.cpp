#include "bus.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = 0x01;
	ram[0x101] = 0xAA;
	ram[0x102] = 0xFF;
	ram[0x103] = 0x11;
	ram[0x104] = 0xAB;
	ram[0x105] = 0xFE;
	ram[0x106] = 0x21;
	ram[0x107] = 0xAC;
	ram[0x108] = 0xFD;
	ram[0x109] = 0x31;
	ram[0x10A] = 0xAD;
	ram[0x10B] = 0xFC;
};

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};