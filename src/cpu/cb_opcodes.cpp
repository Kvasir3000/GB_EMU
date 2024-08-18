#include "cpu.h"

void CPU::init_cb_instruction_table()
{
	cb_instruction_table_map[SWAP_A] =  { "SWAP_A",  8,  &A, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_B] =  { "SWAP_B",  8,  &B, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_C] =  { "SWAP_C",  8,  &C, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_D] =  { "SWAP_D",  8,  &D, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_E] =  { "SWAP_E",  8,  &E, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_H] =  { "SWAP_H",  8,  &H, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_L] =  { "SWAP_L",  8,  &L, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_HL] = { "SWAP_HL", 16, &H, nullptr, &L,      nullptr, &CPU::swap_r1r3 };
}


// Swap upper and lower nibble of r1 register
void CPU::swap_r1()
{
	uint8_t register_value = REG_VAL(one);
	uint8_t a = (register_value << 4);
	uint8_t b = (register_value >> 4);
	uint8_t c = a | b;

	REG_VAL(one) = (register_value << 4) | (register_value >> 4);
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)register_value << 
		        " -> 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Swap upper and lower bytes of 16-bit r1r3 register
void CPU::swap_r1r3()
{
	uint16_t register_value = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	REG_VAL(one) = register_value & 0x00FF;
	REG_VAL(three) = register_value & 0xFF00;
	set_f_register(combine_two_bytes(REG_VAL(one), REG_VAL(three)), 0, 0, 0);

#if defined DEBUG
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = 0x" << register_value <<
		        " -> 0x" << REG_VAL(one) << REG_VAL(three) << F_REG_BITS << "\n";
#endif
}