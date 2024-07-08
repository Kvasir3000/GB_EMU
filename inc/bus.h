#if !defined BUS_H
#define BUS_H
#include <stdint.h>

class BUS
{
public:
	BUS();
	uint8_t read_from_memory(uint64_t memory_addr);
	void write_to_memory(uint64_t memory_addr, uint8_t data);
private:
	 /*
     * For now it stores the memory of the whole system, as I am just implementing CPU at the moment
     * Later on I am planning to add a BUS system implementation with the proper memory mapping
     */
	uint8_t* ram;
};
#endif