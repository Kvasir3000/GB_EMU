#include "cpu.h"

CPU::CPU(BUS* bus)
{
	PC = 0x100;
	SP = 0xFFFF;
	A.register_name = "A";
	B.register_name = "B";
	C.register_name = "C";
	D.register_name = "D";
	E.register_name = "E";
	H.register_name = "H";
	L.register_name = "L";
	F = { 0, 0, 0, 0, 0};

	init_instruction_table();
	this->bus = bus;
	log_file.open("log.txt");
}

void CPU::start_emulation()
{
	while (true)
	{
		tick();
		PC++;
		if (PC == 0x116) return;
	}
}

void CPU::tick()
{
	fetch_opcode();
	decode_instruction();
	execute();
}

void CPU::fetch_opcode()
{
	current_opcode = bus->read_from_memory(PC);
};

void CPU::decode_instruction()
{
	current_instruction = instruction_table_map[current_opcode];

#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << std::setw(2) << std::setfill('0') << 
		         (uint16_t)current_opcode << "-> " << current_instruction.opcode_name;
#endif
}

void CPU::execute()
{
	(this->*(current_instruction.function_ptr))();
}
