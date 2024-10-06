#include "cpu.h"
#include <iostream>

CPU::CPU()
{

}

CPU::CPU(BUS* bus) : bus(bus)
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
	
	halted = false;

	init_instruction_table();
	init_cb_instruction_table();
	cb_instruction = false;
	current_instruction.number_of_cycles = 0;

    log_file.open("log.txt");
}


uint8_t CPU::tick()
{
	handle_interrupts();
	if (!halted)
	{
		fetch_opcode();
		decode_instruction();
		execute();
		PC++;
	}
	else
	{
		current_instruction.number_of_cycles = 4;
	}
	return current_instruction.number_of_cycles;
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

#if defined DEBUG_CPU
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << std::setw(2) << std::setfill('0') <<
		        (cb_instruction ? "CB" : "") << (uint16_t)current_opcode << "-> " <<
		        current_instruction.opcode_name;
#endif
}


void CPU::execute()
{
	(this->*(current_instruction.function_ptr))();
	cb_instruction = false;
}


void CPU::handle_interrupts()
{
	uint8_t interrupt_enable = bus->read_memory(IE);
	uint8_t interrupt_flag = bus->read_memory(IF);
	if (IME)
	{
		if ((interrupt_enable & IE_VBLANK_MASK) && (interrupt_flag & IF_VBLANK_MASK))
		{
			setup_interrupt(INTERRUPT_SRC_VBLANK, interrupt_flag & IF_VBLANK_CLEAR_MASK);
		}
		if ((interrupt_enable & IE_LCD_MASK) && (interrupt_flag & IF_LCD_MASK))
		{
			setup_interrupt(INTERRUPT_SRC_STAT, interrupt_flag & IF_LCD_CLEAR_MASK);
		}
		if ((interrupt_enable & IE_TIMER_MASK) && (interrupt_flag & IF_TIMER_MASK))
		{
			setup_interrupt(INTERRUPT_SRC_TIMER, interrupt_flag & IF_TIMER_CLEAR_MASK);
		}
		if ((interrupt_enable & IE_SERIAL_MASK) && (interrupt_flag & IF_SERIAL_MASK))
		{
			setup_interrupt(INTERRUPT_SRC_SERIAL, interrupt_flag & IF_SERIAL_CLEAR_MASK);
		}
		if ((interrupt_enable & IE_JOYPAD_MASK) && (interrupt_flag & IF_JOYPAD_MASK))
		{
			setup_interrupt(INTERRUPT_SRC_JOYPAD, interrupt_flag & IF_JOYPAD_CLEAR_MASK);
		}
	}
	if (interrupt_enable & interrupt_flag)
	{
		halted = false;
	} 
}


void CPU::setup_interrupt(uint16_t interrupt_pc, uint8_t clear_interrupt)
{
	IME = false;
	bus->write_memory(--SP, (PC & 0xFF00) >> 8);
	bus->write_memory(--SP, PC & 0x00FF);
	PC = interrupt_pc;
	bus->write_memory(IF, clear_interrupt);
}
