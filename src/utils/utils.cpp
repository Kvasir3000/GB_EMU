#include "utils/utils.h"

uint16_t combine_two_bytes(uint8_t high_byte, uint8_t low_byte)
{
	return (high_byte << 8) | low_byte;
}

bool is_half_carry(uint8_t value_one, uint16_t value_two)
{
	return (((value_one & 0x0F) + (value_two & 0x0F)) & 0x10) == 0x10;
}

bool is_carry(uint8_t value_one, uint16_t value_two)
{
	return (((value_one & 0xFF) + (value_two & 0xFF)) & 0x100) == 0x100;
}

bool is_half_carry_signed(int8_t value_one, uint16_t value_two)
{
	return (((value_one & 0x0F) + (value_two & 0x0F)) & 0x10) == 0x10;
}

bool is_carry_signed(int8_t value_one, uint16_t value_two)
{
	return (((value_one & 0xFF) + (value_two & 0xFF)) & 0x100) == 0x100;
}

bool is_half_borrow(uint8_t value_one, uint8_t value_two)
{
	return (value_one & 0xF) < (value_two & 0xF);
}

bool is_borrow(uint8_t value_one, uint8_t value_two)
{
	return value_one < value_two;
}

bool is_half_carry_16_bit(uint16_t value_one, uint16_t value_two)
{
	return ((value_one & 0xFFF) + (value_two & 0xFFF)) > 0xFFF; 
};

bool is_carry_16_bit(uint16_t value_one, uint16_t value_two)
{
	return ((value_one + value_two) > 0xFFFF);
}
