#pragma once

#include <stdint.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "bus.h"
#include "common/timers_defs.h"
#include "common/interrupts_defs.h"
#include "utils/utils.h"
#include "utils/debug.h"
#include "opcodes.h"
#include "cb_opcodes.h"
#include "timers.h"

#undef DEBUG_CPU


class CPU
{
public: 
	CPU();
	CPU(BUS* bus);
	uint8_t tick();

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
	

	uint16_t PC;
	uint16_t SP;
	
	// Miscellaneous functions
	void     set_f_register(bool z, bool n, bool h, bool c);
	uint16_t get_memory_address();
	uint8_t  get_bit_mask(uint16_t offset);
	uint8_t  get_restart_offset();
	bool     check_jump_condition();
 
	BUS*       bus;

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

	uint8_t     current_opcode;
	INSTRUCTION current_instruction;
	bool        cb_instruction;

	INSTRUCTION instruction_table_map[0x100];
	INSTRUCTION cb_instruction_table_map[0x100];
	void        init_instruction_table();
	void        init_cb_instruction_table();

#if defined DEBUG
	std::ofstream log_file;
#else
	std::ofstream log_file;
#endif

	// Fetch-execute
	void fetch_opcode();
	void decode_instruction();
	void execute();

	void handle_interrupts();
	void setup_interrupt(uint16_t interrupt_pc, uint8_t clear_interrupt);
	bool IME;
	bool halted;

	// Instuctions
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
	void add_r1r3_r2r4();
	void add_r1r3_sp();
	void add_sp_n();
	void inc_r1r3();
	void inc_sp();
	void dec_r1r3();
	void dec_sp();
	void daa();
	void cpl();
	void ccf();
	void scf();
	void nop();
	void halt();
	void stop();
	void di();
	void ei();
	void jp_nn();
	void jp_cc_nn();
	void jp_hl();
	void jr_n();
	void jr_cc_n();
	void call_nn();
	void call_cc();
	void rst();
	void ret();
	void ret_cc();
	void reti();

	// CB instructions
	void swap_r1();
	void swap_r1r3();
	template <typename BIT_OPERATION> void register_bit_shift(BIT_OPERATION bit_operation, uint8_t carry_bit);
	template <typename BIT_OPERATION> void memory_data_bit_shift(BIT_OPERATION bit_operation, uint8_t carry_bit);
	void rlc_r1();
	void rlc_r1r3();
	void rl_r1();
	void rl_r1r3();
	void rrc_r1();
	void rrc_r1r3();
	void rr_r1();
	void rr_r1r3();
	void sla_r1();
	void sla_r1r3();
	void sra_r1();
	void sra_r1r3();
	void srl_r1();
	void srl_r1r3();
	void bit_r1();
	void bit_r1r3();
	void set_r1();
	void set_r1r3();
	void res_r1();
	void res_r1r3();
};