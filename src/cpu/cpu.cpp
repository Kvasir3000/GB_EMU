#include "cpu.h"

CPU::CPU(BUS* bus)
{
	PC = 0x100;
	SP = 0xFFFF;
	init_instruction_table();
	this->bus = bus;
	log_file.open("log.txt");
}

void CPU::start_emulation()
{
	while (true)
	{
		execute_instruction();
		PC++;	
		return;
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
#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " << current_instruction.opcode_str;
#endif
	(this->*(current_instruction.function_ptr))();	
}
