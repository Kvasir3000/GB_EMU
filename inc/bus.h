#pragma once

#include <stdint.h>
#include <vector>
#include "common/timers_defs.h"
#include "common/interrupts_defs.h"

#define SB  0xFF01
#define SC  0xFF02

class BUS
{
public:
	BUS();
	BUS(std::vector<uint8_t> program_data);
	uint8_t  read_memory(uint64_t memory_addr);
	void     write_memory(uint64_t memory_addr, uint8_t data);
	void     increment_system_counter();
	uint16_t read_system_counter();
	bool     read_falling_edge_state();
	void     write_falling_edge_state(bool falling_edge_state);

private:
	 /*
     * For now it stores the memory of the whole system, as I am just implementing CPU at the moment
     * Later on I am planning to add a BUS system implementation with the proper memory mapping
     */
	uint8_t* ram;
	uint16_t system_counter;
	bool     falling_edge_state;
};
