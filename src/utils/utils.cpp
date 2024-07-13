#include "utils/utils.h"

uint16_t combine_two_8_bit_registers(uint8_t register_one, uint16_t register_two)
{
	return (register_one << 8) | register_two;
}