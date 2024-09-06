#include "cpu.h"

void CPU::set_f_register(bool z, bool n, bool h, bool c)
{
	F.Z = z;
	F.N = n;
	F.H = h;
	F.C = c;
}

uint16_t CPU::get_memory_address()
{
	uint8_t low_byte = bus->read_memory(++PC);
	uint8_t high_byte = bus->read_memory(++PC);
	return combine_two_bytes(high_byte, low_byte);
}

bool CPU::check_jump_condition()
{
	bool jump = false;
	if ((current_opcode == JP_NZ || current_opcode == JR_NZ || current_opcode == CALL_NZ || current_opcode == RET_NZ) && !F.Z)
	{
		jump = true;
	}
	else if ((current_opcode == JP_Z || current_opcode == JR_Z || current_opcode == CALL_Z || current_opcode == RET_Z) && F.Z)
	{
		jump = true;
	}
	else if ((current_opcode == JP_NC || current_opcode == JR_NC || current_opcode == CALL_NC || current_opcode == RET_NC) && !F.C)
	{
		jump = true;
	}
	else if ((current_opcode == JP_C || current_opcode == JR_C || current_opcode == CALL_C || current_opcode == RET_C) && F.C)
	{
		jump = true;
	}
	return jump;
}


// This function is written for BIT instruction, it calculates the bit position that is going to be checked, based on the opcode value
uint8_t CPU::get_bit_mask(uint16_t offset)
{
	uint8_t row_coef = (current_opcode - offset) >> 4;
	uint8_t column_coef = ((current_opcode & 0x0F) <= 0x7) ? 0 : 1;
	return 1 << (row_coef + (1 * row_coef) + column_coef);
}


uint8_t CPU::get_restart_offset()
{
	uint8_t offset = 0;
	offset |= (current_opcode - 0xC0) & 0xF0;
	offset |= ((current_opcode & 0x0F) == 0x07) ? 0x0 : 0x8;
	return offset;

}