#if! defined CPU_H
#define CPU_H
#include <stdint.h>
#include <string>
#include <fstream>
#include "bus.h"

enum OPCODE
{
	// 8-bit loads
	// LD nn, n  
	LD_A_n = 0x3E,
	LD_B_n = 0x06,
	LD_C_n = 0x0E,
	LD_D_n = 0x16,
	LD_E_n = 0x1E, 
	LD_H_n = 0x26,
	LD_L_n = 0x2E,

	// LD r1, r2; LD n, A 
	LD_A_A = 0x7F, 
	// LD r1, r2
	LD_A_B = 0x78,
	LD_A_C = 0x79,
	LD_A_C_IO = 0xF2,
	LD_A_D = 0x7A,
	LD_A_E = 0x7B, 
	LD_A_H = 0x7C,
	LD_A_L = 0x7D,
	LD_A_BC = 0x0A,
	LD_A_DE = 0x1A,
	LD_A_HL = 0x7E,
	LD_A_nn = 0xFA,

	LD_B_A = 0x47,
	LD_B_B = 0x40, 
	LD_B_C = 0x41,
	LD_B_D = 0x42,
	LD_B_E = 0x43,
	LD_B_H = 0x44,
	LD_B_L = 0x45,
	LD_B_HL = 0x46,

	LD_C_A = 0x4F,
	LD_C_B = 0x48,
	LD_C_C = 0x49,
	LD_C_D = 0x4A,
	LD_C_E = 0x4B,
	LD_C_H = 0x4C,
	LD_C_L = 0x4D,
	LD_C_HL = 0x4E,

	LD_D_A = 0x57,
	LD_D_B = 0x50,
	LD_D_C = 0x51,
	LD_D_D = 0x52,
	LD_D_E = 0x53,
	LD_D_H = 0x54,
	LD_D_L = 0x55,
	LD_D_HL = 0x56,

	LD_E_A = 0x5F,
	LD_E_B = 0x58,
	LD_E_C = 0x59,
	LD_E_D = 0x5A,
	LD_E_E = 0x5B,
	LD_E_H = 0x5C,
	LD_E_L = 0x5D,
	LD_E_HL = 0x5E,

	LD_H_A = 0x67, 
	LD_H_B = 0x60,
	LD_H_C = 0x61,
	LD_H_D = 0x62,
	LD_H_E = 0x63,
	LD_H_H = 0x64,
	LD_H_L = 0x65,
	LD_H_HL = 0x66,

	LD_L_A = 0x6F,
	LD_L_B = 0x68,
	LD_L_C = 0x69,
	LD_L_D = 0x6A,
	LD_L_E = 0x6B,
	LD_L_H = 0x6C,
	LD_L_L = 0x6D,
	LD_L_HL = 0x6E,

	LD_HL_B = 0x70,
	LD_HL_C = 0x71,
	LD_HL_D = 0x72,
	LD_HL_E = 0x73,
	LD_HL_H = 0x74,
	LD_HL_L = 0x75,
	LD_HL_n = 0x36,
	
	LD_BC_A = 0x02,
	LD_DE_A = 0x12,
	LD_nn_A = 0xEA
};

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
	REGISTER F;
	REGISTER H;
	REGISTER L;

	uint16_t PC;
	uint16_t SP;

	BUS* bus;

	struct INSTRUCTION
	{
		OPCODE opcode;
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
	void execute_instruction();
	void fetch_opcode();
	void decode_instruction();
	void execute();


	void ld_r_n();
	void ld_r_nn();
	void ld_r1_r2();
	void ld_r1_r2r4();
	void ld_r1r3_r2();
	void ld_r1r3_n();
	void ld_nn_r();
	void ld_a_c_io();
	
};
#endif