#include "bus.h"

BUS::BUS()
{
	ram = new uint8_t[0xFFFF];
}

uint8_t BUS::read_from_memory(uint64_t memory_addr)
{
	return ram[memory_addr];
};

void BUS::write_to_memory(uint64_t memory_addr, uint8_t data)
{
	ram[memory_addr] = data;
};