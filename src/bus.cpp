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
	system_counter = 0xABCC;
	falling_edge_state = false;
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
		system_counter = 0;
	}
	else if (memory_addr == TAC)
	{
		falling_edge_state &= ((data & TAC_ENABLE_MASK) >> 2);
		ram[TAC] = data;
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


void BUS::increment_system_counter()
{
	system_counter++;
}


uint16_t BUS::read_system_counter()
{
	return system_counter;
}


bool BUS::read_falling_edge_state()
{
	return falling_edge_state;
}

void BUS::write_falling_edge_state(bool falling_edge_state)
{
	this->falling_edge_state = falling_edge_state;
}