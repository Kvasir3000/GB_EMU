#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF];
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));
	ram[0x100] = LD_H_n;
	ram[0x101] = 0x0;
	ram[0x102] = LD_L_n;
	ram[0x103] = 0xBB;
	ram[0xAABB] = 0;
	ram[0x104] = 0xCB;
	ram[0x105] = SET_H_0;
	ram[0x106] = 0xCB;
	ram[0x107] = SET_H_1;
	ram[0x108] = 0xCB;
	ram[0x109] = SET_H_2;
	ram[0x10A] = 0xCB;
	ram[0x10B] = SET_H_3;
	ram[0x10C] = 0xCB;
	ram[0x10D] = SET_H_4;
	ram[0x10E] = 0xCB;
	ram[0x10F] = SET_H_5;
	ram[0x110] = 0xCB;
	ram[0x111] = SET_H_6;
	ram[0x112] = 0xCB;
	ram[0x113] = SET_H_7;

	ram[0x114] = 0xCB;
	ram[0x115] = RES_H_0;
	ram[0x116] = 0xCB;
	ram[0x117] = RES_H_1;
	ram[0x118] = 0xCB;
	ram[0x119] = RES_H_2;
	ram[0x11A] = 0xCB;
	ram[0x11B] = RES_H_3;
	ram[0x11C] = 0xCB;
	ram[0x11D] = RES_H_4;
	ram[0x11E] = 0xCB;
	ram[0x11F] = RES_H_5;
	ram[0x120] = 0xCB;
	ram[0x121] = RES_H_6;
	ram[0x122] = 0xCB;
	ram[0x123] = RES_H_7;
	ram[0x124] = INC_H;
	ram[0x125] = DEC_H;
	ram[0x126] = DEC_H;
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};