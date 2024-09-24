#include "cpu.h"
#include "assert.h"

void CPU::init_cb_instruction_table()
{
	cb_instruction_table_map[SWAP_A] =   { "SWAP_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_B] =   { "SWAP_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_C] =   { "SWAP_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_D] =   { "SWAP_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_E] =   { "SWAP_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_H] =   { "SWAP_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_L] =   { "SWAP_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_HL] =  { "SWAP_HL",  16, &H, nullptr, &L,      nullptr, &CPU::swap_r1r3 };
	cb_instruction_table_map[RLC_A] =    { "RLC_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_B] =    { "RLC_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_C] =    { "RLC_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_D] =    { "RLC_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_E] =    { "RLC_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_H] =    { "RLC_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_L] =    { "RLC_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_HL] =   { "RLC_HL",   16, &H, nullptr, &L,      nullptr, &CPU::rlc_r1r3 };
	cb_instruction_table_map[RL_A] =     { "RL_A",     8,  &A, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_B] =     { "RL_B",     8,  &B, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_C] =     { "RL_C",     8,  &C, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_D] =     { "RL_D",     8,  &D, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_E] =     { "RL_E",     8,  &E, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_H] =     { "RL_H",     8,  &H, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_L] =     { "RL_L",     8,  &L, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_HL] =    { "RL_D",     16, &H, nullptr, &L,      nullptr, &CPU::rl_r1r3 };
	cb_instruction_table_map[RRC_A] =    { "RRC_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_B] =    { "RRC_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_C] =    { "RRC_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_D] =    { "RRC_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_E] =    { "RRC_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_H] =    { "RRC_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_L] =    { "RRC_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_HL] =   { "RRC_HL",   16, &H, nullptr, &L,      nullptr, &CPU::rrc_r1r3 };
	cb_instruction_table_map[RR_A] =     { "RR_A",     8,  &A, nullptr, nullptr, nullptr, &CPU::rr_r1};
	cb_instruction_table_map[RR_B] =     { "RR_B",     8,  &B, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_C] =     { "RR_C",     8,  &C, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_D] =     { "RR_D",     8,  &D, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_E] =     { "RR_E",     8,  &E, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_H] =     { "RR_H",     8,  &H, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_L] =     { "RR_L",     8,  &L, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_HL] =    { "RR_HL",    16, &H, nullptr, &L,      nullptr, &CPU::rr_r1r3 };
	cb_instruction_table_map[SLA_A] =    { "SLA_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_B] =    { "SLA_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_C] =    { "SLA_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::sla_r1 };	
	cb_instruction_table_map[SLA_D] =    { "SLA_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_E] =    { "SLA_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_H] =    { "SLA_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_L] =    { "SLA_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_HL] =   { "SLA_HL",   16, &H, nullptr, &L,      nullptr, &CPU::sla_r1r3 };
	cb_instruction_table_map[SRA_A] =    { "SRA_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_B] =    { "SRA_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_C] =    { "SRA_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_D] =    { "SRA_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_E] =    { "SRA_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_H] =    { "SRA_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_L] =    { "SRA_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_HL] =   { "SRA_HL",   16, &H, nullptr, &L,      nullptr, &CPU::sra_r1r3 };
	cb_instruction_table_map[SRL_A] =    { "SRL_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_B] =    { "SRL_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_C] =    { "SRL_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_D] =    { "SRL_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_E] =    { "SRL_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_H] =    { "SRL_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_L] =    { "SRL_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_HL] =   { "SRL_HL",   16, &H, nullptr, &L,      nullptr, &CPU::srl_r1r3 };
	cb_instruction_table_map[BIT_A_0] =  { "BIT_A_0",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_0] =  { "BIT_B_0",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_0] =  { "BIT_C_0",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_0] =  { "BIT_D_0",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_0] =  { "BIT_E_0",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_0] =  { "BIT_H_0",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_0] =  { "BIT_L_0",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_0] = { "BIT_HL_0", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_1] =  { "BIT_A_1",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_1] =  { "BIT_B_1",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_1] =  { "BIT_C_1",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_1] =  { "BIT_D_1",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_1] =  { "BIT_E_1",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_1] =  { "BIT_H_1",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_1] =  { "BIT_L_1",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_1] = { "BIT_HL_1", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_2] =  { "BIT_A_2",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_2] =  { "BIT_B_2",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_2] =  { "BIT_C_2",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_2] =  { "BIT_D_2",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_2] =  { "BIT_E_2",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_2] =  { "BIT_H_2",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_2] =  { "BIT_L_2",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_2] = { "BIT_HL_2", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_3] =  { "BIT_A_3",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_3] =  { "BIT_B_3",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_3] =  { "BIT_C_3",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_3] =  { "BIT_D_3",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_3] =  { "BIT_E_3",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_3] =  { "BIT_H_3",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_3] =  { "BIT_L_3",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_3] = { "BIT_HL_3", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_4] =  { "BIT_A_4",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_4] =  { "BIT_B_4",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_4] =  { "BIT_C_4",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_4] =  { "BIT_D_4",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_4] =  { "BIT_E_4",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_4] =  { "BIT_H_4",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_4] =  { "BIT_L_4",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_4] = { "BIT_HL_4", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_5] =  { "BIT_A_5",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_5] =  { "BIT_B_5",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_5] =  { "BIT_C_5",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_5] =  { "BIT_D_5",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_5] =  { "BIT_E_5",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_5] =  { "BIT_H_5",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_5] =  { "BIT_L_5",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_5] = { "BIT_HL_5", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_6] =  { "BIT_A_6",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_6] =  { "BIT_B_6",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_6] =  { "BIT_C_6",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_6] =  { "BIT_D_6",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_6] =  { "BIT_E_6",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_6] =  { "BIT_H_6",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_6] =  { "BIT_L_6",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_6] = { "BIT_HL_6", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[BIT_A_7] =  { "BIT_A_7",  8,  &A, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_B_7] =  { "BIT_B_7",  8,  &B, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_C_7] =  { "BIT_C_7",  8,  &C, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_D_7] =  { "BIT_D_7",  8,  &D, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_E_7] =  { "BIT_E_7",  8,  &E, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_H_7] =  { "BIT_H_7",  8,  &H, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_L_7] =  { "BIT_L_7",  8,  &L, nullptr, nullptr, nullptr, &CPU::bit_r1 };
	cb_instruction_table_map[BIT_HL_7] = { "BIT_HL_7", 12, &H, nullptr, &L,      nullptr, &CPU::bit_r1r3 };
	cb_instruction_table_map[SET_A_0] =  { "SET_A_0",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_0] =  { "SET_B_0",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_0] =  { "SET_C_0",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_0] =  { "SET_D_0",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_0] =  { "SET_E_0",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_0] =  { "SET_H_0",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_0] =  { "SET_L_0",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_0] = { "SET_HL_0", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_1] =  { "SET_A_1",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_1] =  { "SET_B_1",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_1] =  { "SET_C_1",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_1] =  { "SET_D_1",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_1] =  { "SET_E_1",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_1] =  { "SET_H_1",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_1] =  { "SET_L_1",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_1] = { "SET_HL_1", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_2] =  { "SET_A_2",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_2] =  { "SET_B_2",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_2] =  { "SET_C_2",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_2] =  { "SET_D_2",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_2] =  { "SET_E_2",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_2] =  { "SET_H_2",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_2] =  { "SET_L_2",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_2] = { "SET_HL_2", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_3] =  { "SET_A_3",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_3] =  { "SET_B_3",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_3] =  { "SET_C_3",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_3] =  { "SET_D_3",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_3] =  { "SET_E_3",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_3] =  { "SET_H_3",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_3] =  { "SET_L_3",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_3] = { "SET_HL_3", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_4] =  { "SET_A_4",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_4] =  { "SET_B_4",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_4] =  { "SET_C_4",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_4] =  { "SET_D_4",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_4] =  { "SET_E_4",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_4] =  { "SET_H_4",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_4] =  { "SET_L_4",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_4] = { "SET_HL_4", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_5] =  { "SET_A_5",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_5] =  { "SET_B_5",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_5] =  { "SET_C_5",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_5] =  { "SET_D_5",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_5] =  { "SET_E_5",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_5] =  { "SET_H_5",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_5] =  { "SET_L_5",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_5] = { "SET_HL_5", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_6] =  { "SET_A_6",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_6] =  { "SET_B_6",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_6] =  { "SET_C_6",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_6] =  { "SET_D_6",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_6] =  { "SET_E_6",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_6] =  { "SET_H_6",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_6] =  { "SET_L_6",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_6] = { "SET_HL_6", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[SET_A_7] =  { "SET_A_7",  8,  &A, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_B_7] =  { "SET_B_7",  8,  &B, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_C_7] =  { "SET_C_7",  8,  &C, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_D_7] =  { "SET_D_7",  8,  &D, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_E_7] =  { "SET_E_7",  8,  &E, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_H_7] =  { "SET_H_7",  8,  &H, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_L_7] =  { "SET_L_7",  8,  &L, nullptr, nullptr, nullptr, &CPU::set_r1 };
	cb_instruction_table_map[SET_HL_7] = { "SET_HL_7", 16, &H, nullptr, &L,      nullptr, &CPU::set_r1r3 };
	cb_instruction_table_map[RES_A_0] =  { "RES_A_0",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_0] =  { "RES_B_0",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_0] =  { "RES_C_0",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_0] =  { "RES_D_0",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_0] =  { "RES_E_0",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_0] =  { "RES_H_0",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_0] =  { "RES_L_0",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_0] = { "RES_HL_0", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_1] =  { "RES_A_1",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_1] =  { "RES_B_1",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_1] =  { "RES_C_1",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_1] =  { "RES_D_1",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_1] =  { "RES_E_1",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_1] =  { "RES_H_1",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_1] =  { "RES_L_1",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_1] = { "RES_HL_1", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_2] =  { "RES_A_2",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_2] =  { "RES_B_2",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_2] =  { "RES_C_2",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_2] =  { "RES_D_2",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_2] =  { "RES_E_2",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_2] =  { "RES_H_2",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_2] =  { "RES_L_2",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_2] = { "RES_HL_2", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_3] =  { "RES_A_3",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_3] =  { "RES_B_3",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_3] =  { "RES_C_3",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_3] =  { "RES_D_3",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_3] =  { "RES_E_3",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_3] =  { "RES_H_3",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_3] =  { "RES_L_3",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_3] = { "RES_HL_3", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_4] =  { "RES_A_4",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_4] =  { "RES_B_4",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_4] =  { "RES_C_4",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_4] =  { "RES_D_4",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_4] =  { "RES_E_4",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_4] =  { "RES_H_4",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_4] =  { "RES_L_4",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_4] = { "RES_HL_4", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_5] =  { "RES_A_5",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_5] =  { "RES_B_5",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_5] =  { "RES_C_5",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_5] =  { "RES_D_5",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_5] =  { "RES_E_5",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_5] =  { "RES_H_5",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_5] =  { "RES_L_5",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_5] = { "RES_HL_5", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_6] =  { "RES_A_6",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_6] =  { "RES_B_6",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_6] =  { "RES_C_6",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_6] =  { "RES_D_6",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_6] =  { "RES_E_6",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_6] =  { "RES_H_6",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_6] =  { "RES_L_6",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_6] = { "RES_HL_6", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
	cb_instruction_table_map[RES_A_7] =  { "RES_A_7",  8,  &A, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_B_7] =  { "RES_B_7",  8,  &B, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_C_7] =  { "RES_C_7",  8,  &C, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_D_7] =  { "RES_D_7",  8,  &D, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_E_7] =  { "RES_E_7",  8,  &E, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_H_7] =  { "RES_H_7",  8,  &H, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_L_7] =  { "RES_L_7",  8,  &L, nullptr, nullptr, nullptr, &CPU::res_r1 };
	cb_instruction_table_map[RES_HL_7] = { "RES_HL_7", 16, &H, nullptr, &L,      nullptr, &CPU::res_r1r3 };
}


// Swap upper and lower nibble of r1 register
void CPU::swap_r1()
{
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) = (register_value << 4) | (register_value >> 4);
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)register_value << 
		        " -> 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Swap upper and lower bytes of 16-bit r1r3 register
void CPU::swap_r1r3()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint8_t  data = bus->read_memory(memory_address);
	bus->write_memory(memory_address, (data << 4) | (data >> 4));
	set_f_register(bus->read_memory(memory_address) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << LOG_MEM_VALUE_CHANGE(memory_address, data) << F_REG_BITS << "\n";
#endif
}


// Wrap function for shifting/rotating bits in register
template <typename BIT_OPERATION>
void CPU::register_bit_shift(BIT_OPERATION bit_operation, uint8_t carry_bit)
{
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) = bit_operation(register_value);
	if (cb_instruction)
	{
		set_f_register(REG_VAL(one) == 0, 0, 0, register_value & carry_bit);
	}
	else
	{
		set_f_register(0, 0, 0, register_value & carry_bit);
	}

#if defined DEBUG_CPU
	log_file << LOG_BIT_SHIFT(one, register_value);
#endif
};


// Wrap function for shifting/rotating bits in a memory address
template <typename BIT_OPERATION>
void CPU::memory_data_bit_shift(BIT_OPERATION bit_operation, uint8_t carry_bit)
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint8_t  data = bus->read_memory(memory_address);
	bus->write_memory(memory_address, bit_operation(data));
	set_f_register(bus->read_memory(memory_address) == 0, 0, 0, data & carry_bit);

#if defined DEBUG_CPU
	log_file << LOG_BIT_SHIFT_ADDR(memory_address, data);
#endif
};


// Rotate r1 register left, put old bit 7 into C flag
void CPU::rlc_r1()
{
	auto rlc = [](uint8_t register_value) -> uint8_t { return (register_value << 1) | (register_value >> 7); };
	register_bit_shift(rlc, 0x80);
}

// Rotate data located at ADDR[r1r3] left, put old bit 7 into C flag
void CPU::rlc_r1r3()
{
	auto rlc = [](uint8_t register_value) -> uint8_t { return (register_value << 1) | (register_value >> 7); };
	memory_data_bit_shift(rlc, 0x80);    
}

// Rotate r1 left, put data from C register to bit 1 and old bit 7 to C register
void CPU::rl_r1()
{
	auto rl = [this](uint8_t register_value) -> uint8_t { return (register_value << 1) | F.C; };
	register_bit_shift(rl, 0x80);
}


// Rotate data located at ADDR[r1r3] left, put data from C register to bit 1 and old bit 7 to C register
void CPU::rl_r1r3()
{
	auto rl = [this](uint8_t register_value) -> uint8_t { return (register_value << 1) | F.C; };
	memory_data_bit_shift(rl, 0x80);
}


// Rotate r1 right, put old bit 0 into C register  
void CPU::rrc_r1()
{
	auto rrc = [](uint8_t register_value) -> uint8_t { return (register_value >> 1) | (register_value << 7); };
	register_bit_shift(rrc, 0x1);
}



// Rotate data from ADDR[r1r34] right, put old bit 0 into C register
void CPU::rrc_r1r3()
{
	auto rrc = [](uint8_t register_value) -> uint8_t { return (register_value >> 1) | (register_value << 7); };
	memory_data_bit_shift(rrc, 0x1);
}


// Rotate r1 right, put data from C register to bit 7 and old bit 0 to C register
void CPU::rr_r1()
{
	auto rr = [this](uint8_t register_value) -> uint8_t { return (register_value >> 1) | (F.C << 7); };
	register_bit_shift(rr, 0x1);
}


// Rotate data from ADDR[r1r34] right, put data from C register to bit 7 and old bit 0 to C register
void CPU::rr_r1r3()
{
	auto rr = [this](uint8_t register_data) -> uint8_t { return (register_data >> 1) | (F.C << 7); };
	memory_data_bit_shift(rr, 0x1);
}


// Shift left r1 register, put data from bit 7 to C register
void CPU::sla_r1()
{
	auto sla = [](uint8_t register_value) -> uint8_t { return register_value << 1; };
	register_bit_shift(sla, 0x80);
} 


// Shift left data in ADDR[r1r3], put data from bit 7 to C register
void CPU::sla_r1r3()
{
	auto sla = [](uint8_t register_value) -> uint8_t {return register_value << 1; };
	memory_data_bit_shift(sla, 0x80);
}


//Shift right r1 register, put data from bit 0 to C register, keep MSB
void CPU::sra_r1()
{
	auto sra = [](uint8_t register_value) -> uint8_t { return (register_value >> 1) | register_value & 0x80; };
	register_bit_shift(sra, 0x1);
}


// Shift left data in ADDR[r1r3], put data from bit 0 to C register, keep MSB
void CPU::sra_r1r3()
{
	auto sra = [](uint8_t register_value) -> uint8_t { return (register_value >> 1) | (register_value & 0x80); };
	memory_data_bit_shift(sra, 0x1);
}


// Shift right r1 register, put data from bit 0 to C register, set MSB to 0 
void CPU::srl_r1()
{
	auto srl = [](uint8_t register_value) -> uint8_t { return (register_value >> 1); };
	register_bit_shift(srl, 0x1);
}


// Shift right ADDR[r1r3], put data from bit 0 to C register, set MSB to 0 
void CPU::srl_r1r3()
{
	auto srl = [](uint8_t register_value) -> uint8_t { return (register_value >> 1); };
	memory_data_bit_shift(srl, 0x1);
}


// Test bit b in register r1
void CPU::bit_r1()
{
	uint8_t bit_mask = get_bit_mask(0x40);
	set_f_register((REG_VAL(one) & bit_mask)  == 0, 0, 1, F.C);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Test bit b in ADDR[r1r3]
void CPU::bit_r1r3()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint16_t data = bus->read_memory(memory_address);
	uint8_t bit_mask = get_bit_mask(0x40);
	set_f_register((data & bit_mask) == 0, 0, 1, F.C);

#if defined DEBUG_CPU
	log_file << ": " << ADDR(memory_address) << "0x" << data << F_REG_BITS << "\n";
#endif
}


// Set bit of r1 register r1 at index b
void CPU::set_r1()
{
	uint8_t bit_mask = get_bit_mask(0xC0);
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) |= bit_mask;

#if defined DEBUG_CPU
	log_file << LOG_REG_VALUE_CHANGE(one, register_value) << "\n";
#endif
}


// Set bit of ADDR[r1r3] at index b
void CPU::set_r1r3()
{
	//assert(false);
	uint16_t memory_address = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint8_t  data = bus->read_memory(memory_address);
	uint8_t bit_mask = get_bit_mask(0xC0);
	bus->write_memory(memory_address, data | bit_mask);

#if defined DEBUG_CPU
	log_file << LOG_MEM_VALUE_CHANGE(memory_address, data) << "\n";
#endif
}


// Reset bit of r1 register r1 at index b
void CPU::res_r1()
{
	uint8_t bit_mask = get_bit_mask(0x80);
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) &= ~bit_mask;

#if defined DEBUG_CPU
	log_file << LOG_REG_VALUE_CHANGE(one, register_value) << "\n";
#endif
}


// Reset bit of ADDR[r1r3] at index b
void CPU::res_r1r3()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint8_t  data = bus->read_memory(memory_address);
	uint8_t bit_mask = get_bit_mask(0x80);
	bus->write_memory(memory_address, data & (~bit_mask));

#if defined DEBUG_CPU
	log_file << LOG_MEM_VALUE_CHANGE(memory_address, data) << "\n";
#endif
}