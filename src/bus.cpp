#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_A_n;
	ram[0x101] = 0xF0;
	ram[0x102] = LD_B_n;
	ram[0x103] = 0x10;
	ram[0x104] = ADD_A_B;
	ram[0x105] = JR_C;
	ram[0x106] = 0xFF;
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};