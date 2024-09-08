#pragma once

#include <stdint.h>
#include <vector>

#define SB  0xFF01
#define SC  0xFF02

class BUS
{
public:
	BUS(std::vector<uint8_t> program_data);
	uint8_t read_memory(uint64_t memory_addr);
	void write_memory(uint64_t memory_addr, uint8_t data);
private:
	 /*
     * For now it stores the memory of the whole system, as I am just implementing CPU at the moment
     * Later on I am planning to add a BUS system implementation with the proper memory mapping
     */
	uint8_t* ram;
};
