#include <stdint.h>

// Util macro to access registers in instructions
#define REG_VAL(parameter_value)   current_instruction.parameter_##parameter_value->register_value

uint16_t combine_two_bytes(uint8_t high_byte, uint8_t low_byte);

bool is_half_carry(uint8_t value_one, uint16_t value_two);

bool is_carry(uint8_t value_one, uint16_t value_two);

bool is_half_carry_signed(int8_t value_one, uint16_t value_two);

bool is_carry_signed(int8_t value_one, uint16_t value_two);

bool is_half_borrow(uint8_t value_one, uint8_t value_two);

bool is_borrow(uint8_t value_one, uint8_t value_two);

bool is_half_carry_16_bit(uint16_t value_one, uint16_t value_two);

bool is_carry_16_bit(uint16_t value_one, uint16_t value_two);