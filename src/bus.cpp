#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_A_n;
	ram[0x101] = 0x12;
	ram[0x102] = LD_B_n;
	ram[0x103] = 0x21;
	ram[0x104] = LD_C_n;
	ram[0x105] = 0x35;
	ram[0x106] = LD_D_n;
	ram[0x107] = 0x53;
	ram[0x108] = LD_E_n;
	ram[0x109] = 0x64;
	ram[0x10A] = LD_H_n;
	ram[0x10B] = 0x46;
	ram[0x10C] = LD_L_n;
	ram[0x10D] = 0x27;
	ram[0x10E] = 0xCB;
	ram[0x10F] = SWAP_A;
	ram[0x110] = 0xCB;
	ram[0x111] = SWAP_B;
	ram[0x112] = 0xCB;
	ram[0x113] = SWAP_C;
	ram[0x114] = 0xCB;
	ram[0x115] = SWAP_D;
	ram[0x116] = 0xCB;
	ram[0x117] = SWAP_E;
	ram[0x118] = 0xCB;
	ram[0x119] = SWAP_H;
	ram[0x11A] = 0xCB;
	ram[0x11B] = SWAP_L;
	ram[0x11C] = 0xCB;
	ram[0x11D] = SWAP_HL;
}; 

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};