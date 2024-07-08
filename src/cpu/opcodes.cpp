#include "cpu.h"
#include <cassert>

void CPU::init_instruction_table()
{
	instruction_table_map[LD_B_n] = { LD_B_n, 8, &B, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
	instruction_table_map[LD_C_n] = { LD_C_n, 8, &C, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
	instruction_table_map[LD_D_n] = { LD_D_n, 8, &D, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
	instruction_table_map[LD_E_n] = { LD_E_n, 8, &E, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
	instruction_table_map[LD_H_n] = { LD_H_n, 8, &H, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
	instruction_table_map[LD_L_n] = { LD_L_n, 8, &L, nullptr, nullptr, nullptr, 1, &CPU::ld_nn_to_register };
}

void CPU::ld_nn_to_register()
{
	if (current_instruction.instruction_length == 2)
	{
		// This code path is untested !!! 
		assert(false);
		*current_instruction.parameter_three = bus->read_from_memory(++PC); // LSB
		*current_instruction.parameter_one = bus->read_from_memory(++PC);   // MSB 
	}
	else if (current_instruction.instruction_length == 1)
	{
		*current_instruction.parameter_one = bus->read_from_memory(++PC);
	}
}