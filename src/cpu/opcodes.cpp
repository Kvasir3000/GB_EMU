#include "cpu.h"
#include <cassert>

void CPU::init_instruction_table()
 {
	instruction_table_map[LD_B_n] =  { LD_B_n,  "LD_B_n",   8,  &B, nullptr, nullptr, nullptr, &CPU::ld_r_n};
	instruction_table_map[LD_C_n] =  { LD_C_n,  "LD_C_n",   8,  &C, nullptr, nullptr, nullptr, &CPU::ld_r_n };
	instruction_table_map[LD_D_n] =  { LD_D_n,  "LD_D_n",   8,  &D, nullptr, nullptr, nullptr, &CPU::ld_r_n };
	instruction_table_map[LD_E_n] =  { LD_E_n,  "LD_E_n",   8,  &E, nullptr, nullptr, nullptr, &CPU::ld_r_n };
	instruction_table_map[LD_H_n] =  { LD_H_n,  "LD_H_n",   8,  &H, nullptr, nullptr, nullptr, &CPU::ld_r_n };
	instruction_table_map[LD_L_n] =  { LD_L_n,  "LD_L_n",   8,  &L, nullptr, nullptr, nullptr, &CPU::ld_r_n };
	instruction_table_map[LD_A_A] =  { LD_A_A,  "LD_A_A",   4,  &A, &A,      nullptr, nullptr, &CPU::ld_r1_r2 }; 
	instruction_table_map[LD_A_B] =  { LD_A_B,  "LD_A_B",   4,  &A, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_C] =  { LD_A_C,  "LD_A_C",   4,  &A, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_D] =  { LD_A_D,  "LD_A_D",   4,  &A, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_E] =  { LD_A_E,  "LD_A_E",   4,  &A, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_H] =  { LD_A_H,  "LD_A_H",   4,  &A, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_L] =  { LD_A_L,  "LD_A_L",   4,  &A, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_HL] = { LD_A_HL, "LD_A_HL",  8,  &A, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_B_B] =  { LD_B_B,  "LD_B_B",   4,  &B, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_C] =  { LD_B_C,  "LD_B_C",   4,  &B, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_D] =  { LD_B_D,  "LD_B_D",   4,  &B, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_E] =  { LD_B_E,  "LD_B_E",   4,  &B, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_H] =  { LD_B_H,  "LD_B_H",   4,  &B, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_L] =  { LD_B_L,  "LD_B_L",   4,  &B, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_HL] = { LD_B_HL, "LD_B_HL",  8,  &B, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_C_B] =  { LD_C_B,  "LD_C_B",   4,  &C, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_C] =  { LD_C_C,  "LD_C_C",   4,  &C, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_D] =  { LD_C_D,  "LD_C_D",   4,  &C, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_E] =  { LD_C_E,  "LD_C_E",   4,  &C, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_H] =  { LD_C_H,  "LD_C_H",   4,  &C, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_L] =  { LD_C_L,  "LD_C_L",   4,  &C, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_HL] = { LD_C_HL, "LD_C_HL",  8,  &C, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_D_B] =  { LD_D_B,  "LD_D_B",   4,  &D, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_C] =  { LD_D_C,  "LD_D_C",   4,  &D, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_D] =  { LD_D_D,  "LD_D_D",   4,  &D, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_E] =  { LD_D_E,  "LD_D_E",   4,  &D, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_H] =  { LD_D_H,  "LD_D_H",   4,  &D, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_L] =  { LD_D_L,  "LD_D_L",   4,  &D, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_HL] = { LD_D_HL, "LD_D_HL",  8,  &D, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_E_B] =  { LD_E_B,  "LD_E_B",   4,  &E, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_C] =  { LD_E_C,  "LD_E_C",   4,  &E, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_D] =  { LD_E_D,  "LD_E_D",   4,  &E, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_E] =  { LD_E_E,  "LD_E_E",   4,  &E, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_H] =  { LD_E_H,  "LD_E_H",   4,  &E, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_L] =  { LD_E_L,  "LD_E_L",   4,  &E, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_HL] = { LD_E_HL, "LD_E_HL",  8,  &E, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_H_B] =  { LD_H_B,  "LD_H_B",   4,  &H, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_C] =  { LD_H_C,  "LD_H_C",   4,  &H, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_D] =  { LD_H_D,  "LD_H_D",   4,  &H, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_E] =  { LD_H_E,  "LD_H_E",   4,  &H, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_H] =  { LD_H_H,  "LD_H_H",   4,  &H, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_L] =  { LD_H_L,  "LD_H_L",   4,  &H, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_HL] = { LD_H_HL, "LD_H_HL",  8,  &H, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_L_B] =  { LD_L_B,  "LD_L_B",   4,  &L, &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_C] =  { LD_L_C,  "LD_L_C",   4,  &L, &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_D] =  { LD_L_D,  "LD_L_D",   4,  &L, &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_E] =  { LD_L_E,  "LD_L_E",   4,  &L, &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_H] =  { LD_L_H,  "LD_L_H",   4,  &L, &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_L] =  { LD_L_L,  "LD_L_L",   4,  &L, &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_HL] = { LD_L_HL, "LD_L_HL",  8,  &L, &H,      nullptr, &L,      &CPU::ld_r_hl };
	instruction_table_map[LD_HL_B] = { LD_HL_B, "LD_HL_B",  8,  &H, &B,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_C] = { LD_HL_C, "LD_HL_C",  8,  &H, &C,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_D] = { LD_HL_D, "LD_HL_D",  8,  &H, &D,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_E] = { LD_HL_E, "LD_HL_E",  8,  &H, &E,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_H] = { LD_HL_H, "LD_HL_H",  8,  &H, &H,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_L] = { LD_HL_L, "LD_HL_L",  8,  &H, &L,      &L,      nullptr, &CPU::ld_hl_r };
	instruction_table_map[LD_HL_n] = { LD_HL_n, "LD_HL_n",  12, &H, &H,      &L,      nullptr, &CPU::ld_hl_n };
}

void CPU::ld_r_n()
{
	current_instruction.parameter_one->register_value = bus->read_from_memory(++PC);
#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = 0x" <<
		                (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}

void CPU::ld_r1_r2()
{
	current_instruction.parameter_one->register_value = current_instruction.parameter_two->register_value;
#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = " << 
		                current_instruction.parameter_two->register_name << " = 0x" << 
		                (uint16_t)current_instruction.parameter_one->register_value  << "\n";
#endif
}

void CPU::ld_r_hl()
{
	uint16_t memory_addr = (current_instruction.parameter_two->register_value << 8) | 
		                    current_instruction.parameter_four->register_value;
	current_instruction.parameter_one->register_value = bus->read_from_memory(memory_addr);
#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = " <<
		                "ADDR[0x" << memory_addr << "] = 0x" << 
						 (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}

void CPU::ld_hl_r()
{
	uint16_t memory_addr = (current_instruction.parameter_one->register_value << 8) |
		                    current_instruction.parameter_three->register_value;
	bus->write_to_memory(memory_addr, current_instruction.parameter_two->register_value);
#if defined DEBUG
	log_file << ": ADDR[0x" << memory_addr << "] = " << current_instruction.parameter_two->register_name << 
		        " = 0x" << (uint16_t)current_instruction.parameter_two->register_value << "\n";
#endif
}

void CPU::ld_hl_n()
{
	uint16_t memory_addr = (current_instruction.parameter_one->register_value << 8) | 
		                    current_instruction.parameter_three->register_value;
	uint8_t  data = bus->read_from_memory(++PC);
	bus->write_to_memory(memory_addr, data);
#if defined DEBUG
	log_file << ": ADDR[0x" << memory_addr << "] = " << (uint16_t)data << "\n";
#endif
}

