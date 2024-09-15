#include "cpu.h"

CPU::CPU(BUS* bus)
{
	A = { 0x01, "A" };
	B = { 0xFF, "B" };
	C = { 0x13, "C" };
	D = { 0x00, "D" };
	E = { 0xC1, "E" };
	H = { 0x84, "H" };
	L = { 0x03, "L" };
	F = { 0, 0, 0, 0, 0 };
	PC = 0x100;
	SP = 0xFFFE;
	
	cb_instruction = false;
	halted = false;

	init_instruction_table();
	init_cb_instruction_table();
	this->bus = bus;
	log_file.open("log.txt");
}

void CPU::start_emulation()
{
	while (!halted)
	{
		tick();
		PC++;
	}
}

void CPU::tick()
{
	if (!halted)
	{
		fetch_opcode();
		decode_instruction();
		execute();
	}
}

void CPU::fetch_opcode()
{
	current_opcode = bus->read_memory(PC);
	if (current_opcode == 0xCB)
	{
		current_opcode = bus->read_memory(++PC);
		cb_instruction = true;
	}
};

void CPU::decode_instruction()
{
	if (cb_instruction)
	{
		current_instruction = cb_instruction_table_map[current_opcode];
	}
	else
	{
		current_instruction = instruction_table_map[current_opcode];
	}

#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << std::setw(2) << std::setfill('0') << 
		         (cb_instruction? "CB" : "") << (uint16_t)current_opcode << "-> " << 
		         current_instruction.opcode_name;
#else 
	//log_file << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << PC << "\n";
#endif
}

void CPU::execute()
{
	(this->*(current_instruction.function_ptr))();
	cb_instruction = false;
}


