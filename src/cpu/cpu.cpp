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
	cb_instruction = false;
	halted = false;

	init_instruction_table();
	init_cb_instruction_table();
	this->bus = bus;
	log_file.open("log.txt");
}

void CPU::start_emulation()
{
	while (true)
	{
		tick();
		PC++;
		if (PC == 0x107) return;
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
#endif
}

void CPU::execute()
{
	(this->*(current_instruction.function_ptr))();
	cb_instruction = false;
}


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
	if ((current_opcode == JP_NZ || current_opcode == JR_NZ) && !F.Z)
	{
		jump = true;
	}
	else if ((current_opcode == JP_Z || current_opcode == JR_Z) && F.Z)
	{
		jump = true;
	}
	else if ((current_opcode == JP_NC || current_opcode == JR_NC) && !F.C)
	{
		jump = true;
	}
	else if ((current_opcode == JP_C || current_opcode == JR_C) && F.C)
	{
		jump = true;
	}
	return jump;
}