#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_SP_nn;
	ram[0x101] = 0x23;
	ram[0x102] = 0x14;
	ram[0x103] = LD_A_n;
	ram[0x104] = 0x5;
	ram[0x105] = LD_B_n;
	ram[0x106] = 0x4;
	ram[0x107] = SUB_B;
	ram[0x108] = CALL_NZ;
	ram[0x109] = 0x23;
	ram[0x10A] = 0x20;
	ram[0x2023] = RST_28;
	ram[0x0028] = RET_NZ;
	ram[0x2024] = LD_B_n;
	ram[0x2025] = 0x1;
	ram[0x2026] = SUB_B;
	ram[0x2027] = RETI;
	ram[0x10B] = NOP;
	//ram[0x2025] = NOP;
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};