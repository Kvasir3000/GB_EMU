#include "bus.h"
#include "opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_A_n;
	ram[0x101] = 0xFF;
	ram[0x102] = LD_B_n;
	ram[0x103] = 0b11;
	ram[0x104] = LD_C_n;
	ram[0x105] = 0b100;
	ram[0x106] = LD_D_n;
	ram[0x107] = 1;
	ram[0x108] = LD_E_n;
	ram[0x109] = 0b10000;
	ram[0x10A] = LD_H_n;
	ram[0x10B] = 0b100000;
	ram[0x10C] = LD_L_n;
	ram[0x10D] = 0b1000000;
	ram[0x10E] = DEC_A;
	ram[0x10F] = DEC_B;
	ram[0x110] = DEC_C;
	ram[0x111] = DEC_D;
	ram[0x112] = DEC_E;
	ram[0x113] = DEC_H;
	ram[0x114] = DEC_L;
	ram[0x1f3f] = 0;
	ram[0x115] = DEC_HL_A;
	ram[0x116] = CP_n;
	ram[0x117] = 0b10000000;
}; 

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};