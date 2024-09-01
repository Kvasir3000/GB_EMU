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

bool is_half_carry(int8_t value_one, uint16_t value_two)
{
	return (((value_one & 0x0F) + (value_two & 0x0F)) & 0x10) == 0x10;
}

bool is_carry(int8_t value_one, uint16_t value_two)
{
	return (((value_one & 0xFF) + (value_two & 0xFF)) & 0x100) == 0x100;
}

bool is_half_borrow(uint8_t value_one, uint8_t value_two)
{
	return ((value_one & 0x0F) - (value_two & 0x0F)) < 0;
}

bool is_borrow(uint8_t value_one, uint8_t value_two)
{
	return (value_one - value_two) < 0;
}

bool is_half_carry_16_bit(uint16_t value_one, uint16_t value_two)
{
	return ((value_one & 0xFFF) + (value_two & 0xFFF)) > 0xFFF; 
};

bool is_carry_16_bit(uint16_t value_one, uint16_t value_two)
{
	return ((value_one + value_two) > 0xFFFF);
}


// This function is written for BIT instruction, it calculates the bit position that is going to be checked, based on the opcode value
uint8_t get_bit_mask(uint8_t opcode, uint16_t offset)
{
	uint8_t row_coef = (opcode - offset) >> 4;
	uint8_t column_coef = ((opcode & 0x0F) <= 0x7) ? 0 : 1;
	return 1 << (row_coef + (1 * row_coef) + column_coef);
}