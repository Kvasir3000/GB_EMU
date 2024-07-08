#if! defined CPU_H
#define CPU_H
#include <stdint.h>
#include "bus.h"

enum OPCODE
{
	// 8-bit loads
	// LD nn, n  -> put value nn into n 
	LD_B_n = 0x06,
	LD_C_n = 0x0E,
	LD_D_n = 0x16,
	LD_E_n = 0x1E, 
	LD_H_n = 0x26,
	LD_L_n = 0x2E,
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
	uint8_t A;
	uint8_t B;
	uint8_t C;
	uint8_t D;
	uint8_t E;
	uint8_t F;
	uint8_t H;
	uint8_t L;

	uint16_t PC;
	uint16_t SP;

	BUS* bus;

	struct INSTRUCTION
	{
		OPCODE opcode;

		uint8_t number_of_cycles;
		
		uint8_t* parameter_one;
		uint8_t* parameter_two;
		uint8_t* parameter_three; // combined with param_one to form  16 bit register
		uint8_t* parameter_four; // combined with param_two to form 16 bit register

		uint8_t instruction_length;

		void (CPU::* function_ptr)();
	};

	uint8_t current_opcode;
	INSTRUCTION current_instruction;

	INSTRUCTION instruction_table_map[0xFF];
	void init_instruction_table();

	void execute_instruction();
	void fetch_opcode();
	void decode_instruction();


	void ld_nn_to_register();
};
#endif