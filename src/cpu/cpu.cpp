#include "cpu.h"
#include <iostream>

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
	
	div_counter = 255;
	tima_counter = 0;
	halted = false;

	init_instruction_table();
	init_cb_instruction_table();
	cb_instruction = false;
	current_instruction.number_of_cycles = 0;
	current_phase = PHASE_ONE;

	this->bus = bus;
	log_file.open("log.txt");
}

void CPU::start_emulation()
{
	while (true)
	{
		if (IME)
		{
			handle_interrupts();
		}
		tick();
		update_timers();
	}
}

void CPU::tick()
{
	if (!halted)
	{
		if (current_instruction.number_of_cycles == 0)
		{
			fetch_opcode();
			decode_instruction();
			current_instruction.number_of_cycles--;

		}
		else if (current_instruction.number_of_cycles == 1)
		{
			execute();
			PC++;
			current_instruction.number_of_cycles--;
		}
		else
		{
			current_instruction.number_of_cycles--;
		}

#if defined DEBUG_TIMERS
		//log_file << "PC:0x" << std::hex << PC << current_instruction.opcode_name << 
		//	         " :" << (uint16_t)current_instruction.number_of_cycles << "\n";
#endif
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


void CPU::update_timers()
{
	update_div();
	update_tima();
}


void CPU::update_div()
{
	if (div_counter == 0)
	{
		bus->increment_div();
		div_counter = DIV_FREQ_CLK;

#if defined DEBUG_TIMERS
		log_file << std::hex << "PC: 0x" << PC << " DIV = 0x" << (uint16_t)bus->read_memory(DIV) << "\n";
#endif
	}
	else
	{
		div_counter--;
	}
}


void CPU::update_tima()
{
	uint8_t timer_counter = bus->read_memory(TIMA);
	uint8_t timer_control = bus->read_memory(TAC);
	//if (reload_tima)
	//{
	//	reload_tima_cycles--;
	//	if (reload_tima_cycles == 0)
	//	{
	//		reload_tima = false;
	//		bus->write_memory(TIMA, bus->read_memory(TMA));
	//	}
	//}
	if (timer_control & TAC_ENABLE_MASK)
	{
		uint8_t clock = timer_control & TAC_CLOCK_MASK;

		if (tima_counter == 0 && timer_counter == 0xFF)
		{
			reload_tima = true;
			reload_tima_cycles = 4;
			tima_counter = get_tima_frequency(clock);
			uint8_t interrupt_flag = bus->read_memory(IF);
			bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
			bus->write_memory(TIMA, bus->read_memory(TMA));

#if defined DEBUG_TIMERS
			log_file << std::hex << "PC: 0x" << PC << " TIMA = TMA = 0x" << (uint16_t)bus->read_memory(DIV) << "\n";
#endif
		}
		else if (tima_counter == 0)
		{
			bus->increment_tima();
			tima_counter = get_tima_frequency(clock);

#if defined DEBUG_TIMERS
			log_file << std::hex << "PC: 0x" << PC << " TIMA = 0x" << (uint16_t)bus->read_memory(TIMA) << "\n";
#endif
		}
		else
		{
			tima_counter--;
		}
	}
}


void CPU::handle_interrupts()
{
	uint8_t interrupt_enable = bus->read_memory(IE);
	uint8_t interrupt_flag = bus->read_memory(IF);
	if ((interrupt_enable & IE_VBLANK_MASK) && (interrupt_flag & IF_VBLANK_MASK))
	{
		IME = false;
		push_current_pc();
		PC = INTERRUPT_SRC_VBLANK;
		bus->write_memory(IF, interrupt_flag & IF_VBLANK_CLEAR_MASK);
	}
	if ((interrupt_enable & IE_LCD_MASK) && (interrupt_flag & IF_LCD_MASK))
	{
		IME = false;
		push_current_pc();
		PC = INTERRUPT_SRC_STAT;
		bus->write_memory(IF, interrupt_flag & IF_LCD_CLEAR_MASK);

	}
	if ((interrupt_enable & IE_TIMER_MASK) && (interrupt_flag & IF_TIMER_MASK))
	{
		IME = false;
		push_current_pc();
		PC = INTERRUPT_SRC_TIMER;
		bus->write_memory(IF, interrupt_flag & IF_TIMER_CLEAR_MASK);

	}
	if ((interrupt_enable & IE_SERIAL_MASK) && (interrupt_flag & IF_SERIAL_MASK))
	{
		IME = false;
		push_current_pc();
		PC = INTERRUPT_SRC_SERIAL;
		bus->write_memory(IF, interrupt_flag & IF_SERIAL_CLEAR_MASK);
	}
	if ((interrupt_enable & IE_JOYPAD_MASK) && (interrupt_flag & IF_JOYPAD_MASK))
	{
		IME = false;
		push_current_pc();
		PC = INTERRUPT_SRC_JOYPAD;
		bus->write_memory(IF, interrupt_flag & IF_JOYPAD_CLEAR_MASK);
	}
}