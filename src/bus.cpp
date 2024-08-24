#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_A_n;
	ram[0x101] = 0x234;
	ram[0x102] = LD_B_n;
	ram[0x103] = 0xA;
	ram[0x104] = SUB_B;
	ram[0x105] = DAA;
	ram[0x106] = CPL;
	ram[0x107] = CCF;
	ram[0x108] = SCF;
	ram[0x109] = NOP;
	ram[0x10A] = HALT;
}; 

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};