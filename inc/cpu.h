#pragma once

#include <stdint.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "bus.h"
#include "utils/utils.h"
#include "opcodes.h"

class CPU
{
public: 
	CPU(BUS* bus);
	void start_emulation();

private:

	/* 
	* 8-bit  registers, these can be combined to 16 bits in following configurations:
	* AF, BC, DE, HL
	*/
	struct REGISTER
	{
		uint8_t register_value;
		std::string register_name;
	};
	REGISTER A;
	REGISTER B;
	REGISTER C;
	REGISTER D;
	REGISTER E;
	REGISTER H;
	REGISTER L;

	struct FLAG_REGISTER
	{
		uint8_t Z : 1;
		uint8_t N : 1;
		uint8_t H : 1;
		uint8_t C : 1;
		uint8_t free_bits : 4;
	} F;
	void set_f_register(bool z, bool n, bool h, bool c);

	uint16_t PC;
	uint16_t SP;

	BUS* bus;

	struct INSTRUCTION
	{
		std::string opcode_name;
		uint8_t number_of_cycles;
		
		REGISTER* parameter_one;
		REGISTER* parameter_two;
		REGISTER* parameter_three; // combined with param_one to form  16 bit register
		REGISTER* parameter_four; // combined with param_two to form 16 bit register

		void (CPU::* function_ptr)();
	};

	uint8_t current_opcode;
	INSTRUCTION current_instruction;

	INSTRUCTION instruction_table_map[0xFF];
	void init_instruction_table();

#if defined DEBUG
	std::ofstream log_file;
#endif
	void tick();
	void fetch_opcode();
	void decode_instruction();
	void execute();


	void ld_r1_n();
	void ld_r1_nn();
	void ldh_r1_n();
	void ld_r1_r2();
	void ld_r1_r2r4();
	void ldd_r1_r2r4();
	void ldi_r1_r2r4();
	void ld_r1r3_r2();
	void ldd_r1r3_r2();
	void ldi_r1r3_r2();
	void ld_r1r3_n();
	void ld_nn_r1();
	void ldh_n_r1();
	void ld_a_c_io();
	void ld_c_a_io();
	void ld_r1r3_nn();
	void ld_sp_nn();
	void ld_sp_r1r3();
	void ld_r1r3_sp_n();
	void ld_nn_sp();
	void push_af();
	void push_r1r3();
	void pop_af();
	void pop_r1r3();
	void add_r1_r2();
	void add_r1_r2r4();
	void add_r1_n();
	void adc_r1_r2();
	void adc_r1_r2r4();
	void adc_r1_n();
	void sub_r1_r2();
	void sub_r1_r2r4();
	void sub_r1_n();
	void sbc_r1_r2();
	void sbc_r1_r2r4();
	void sbc_r1_n();
	void and_r1_r2();
	void and_r1_r2r4();
	void and_r1_n();
	void or_r1_r2();
	void or_r1_r2r4();
	void or_r1_n();
	void xor_r1_r2();
	void xor_r1_r2r4();
	void xor_r1_n();
	void cp_r1_r2();
	void cp_r1_r2r4();
	void cp_r1_n();
	void inc_r1();
	void inc_r2r4();
	void dec_r1();
	void dec_r2r4();
	void add_sp_n();
	void inc_r1r3();
	void inc_sp();
	void dec_r1r3();
	void dec_sp();
};