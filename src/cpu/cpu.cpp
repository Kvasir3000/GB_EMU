#include "cpu.h"


CPU::CPU(BUS* bus)
{
	PC = 0x100;
	SP = 0xFFFF;
	init_instruction_table();
	this->bus = bus;
}

void CPU::start_emulation()
{
	while (true)
	{
		execute_instruction();
		PC++;	
	}
}

void CPU::execute_instruction()
{
	fetch_opcode();
	decode_instruction();
}

void CPU::fetch_opcode()
{
	current_opcode = bus->read_from_memory(PC);
};

void CPU::decode_instruction()
{
	current_instruction = instruction_table_map[current_opcode];

	(this->*(current_instruction.function_ptr))();	
}
