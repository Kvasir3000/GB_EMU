#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"
#include <iostream>

static char dbg_msg[7000] = { 0 };
static int msg_size = 0;

BUS::BUS(std::vector<uint8_t> program_data)
{
	ram = new uint8_t[0xFFFF + 1];
	uint8_t col = 0;
	uint8_t row = 0;
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));

	ram[DIV] = 0x00;
	ram[TIMA] = 0x00;
	ram[TMA] = 0x00;
	ram[TAC] = 0xF8;
	ram[IF] = 0xE1;
	ram[IE] = 0x00;
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	if (memory_addr == DIV)
	{
		ram[DIV] = 0;
	}
	else
	{
		ram[memory_addr] = data;
		if (memory_addr == SC && ram[SC] == 0x81)
		{
			char c = read_memory(SB);

			dbg_msg[msg_size++] = c;

			write_memory(SC, 0);
			printf("DBG: %s\n", dbg_msg);
		}
	}	
};


void BUS::increment_div()
{
	ram[DIV]++;
}


void BUS::increment_tima()
{
	ram[TIMA]++;
}