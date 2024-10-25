#include "cpu.h"
#include <cassert>

void CPU::init_instruction_table()
{
	instruction_table_map[LD_A_n] =     { "LD_A_n",     8,  &A,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_B_n] =     { "LD_B_n",     8,  &B,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_C_n] =     { "LD_C_n",     8,  &C,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_D_n] =     { "LD_D_n",     8,  &D,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_E_n] =     { "LD_E_n",     8,  &E,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_H_n] =     { "LD_H_n",     8,  &H,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_L_n] =     { "LD_L_n",     8,  &L,      nullptr, nullptr, nullptr, &CPU::ld_r1_n };
	instruction_table_map[LD_A_A] =     { "LD_A_A",     4,  &A,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 }; 
	instruction_table_map[LD_A_B] =     { "LD_A_B",     4,  &A,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_C] =     { "LD_A_C",     4,  &A,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_C_IO]  = { "LD_A_(C)",   8,  &A,      &C,      nullptr, nullptr, &CPU::ld_a_c_io };
	instruction_table_map[LD_A_D] =     { "LD_A_D",     4,  &A,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_E] =     { "LD_A_E",     4,  &A,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_H] =     { "LD_A_H",     4,  &A,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_L] =     { "LD_A_L",     4,  &A,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_A_BC] =    { "LD_A_BC",    8,  &A,      &B,      nullptr, &C,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_A_DE] =    { "LD_A_DE",    8,  &A,      &D,      nullptr, &E,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_A_HL] =    { "LD_A_HL",    8,  &A,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LDD_A_HL]  =  { "LDD_A_HL",   8,  &A,      &H,      nullptr, &L,      &CPU::ldd_r1_r2r4 };
	instruction_table_map[LDI_A_HL]  =  { "LDI_A_HL",   8,  &A,      &H,      nullptr, &L,      &CPU::ldi_r1_r2r4 };
	instruction_table_map[LD_A_nn] =    { "LD_A_nn",    16, &A,      nullptr, nullptr, nullptr, &CPU::ld_r1_nn };
	instruction_table_map[LDH_A_n] =    { "LDH_A_n",    12, &A,      nullptr, nullptr, nullptr, &CPU::ldh_r1_n };
	instruction_table_map[LD_B_A] =     { "LD_B_A",     4,  &B,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_B] =     { "LD_B_B",     4,  &B,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_C] =     { "LD_B_C",     4,  &B,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_D] =     { "LD_B_D",     4,  &B,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_E] =     { "LD_B_E",     4,  &B,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_H] =     { "LD_B_H",     4,  &B,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_L] =     { "LD_B_L",     4,  &B,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_B_HL] =    { "LD_B_HL",    8,  &B,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_C_A] =     { "LD_C_A",     4,  &C,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_A_IO ] = { "LD_(C)_A" ,  8,  &C,      &A,      nullptr, nullptr, &CPU::ld_c_a_io };
	instruction_table_map[LD_C_B] =     { "LD_C_B",     4,  &C,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_C] =     { "LD_C_C",     4,  &C,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_D] =     { "LD_C_D",     4,  &C,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_E] =     { "LD_C_E",     4,  &C,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_H] =     { "LD_C_H",     4,  &C,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_L] =     { "LD_C_L",     4,  &C,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_C_HL] =    { "LD_C_HL",    8,  &C,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_D_A] =     { "LD_D_A",     4,  &D,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_B] =     { "LD_D_B",     4,  &D,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_C] =     { "LD_D_C",     4,  &D,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_D] =     { "LD_D_D",     4,  &D,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_E] =     { "LD_D_E",     4,  &D,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_H] =     { "LD_D_H",     4,  &D,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_L] =     { "LD_D_L",     4,  &D,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_D_HL] =    { "LD_D_HL",    8,  &D,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_E_A] =     { "LD_E_A",     4,  &E,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_B] =     { "LD_E_B",     4,  &E,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_C] =     { "LD_E_C",     4,  &E,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_D] =     { "LD_E_D",     4 , &E,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_E] =     { "LD_E_E",     4,  &E,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_H] =     { "LD_E_H",     4,  &E,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_L] =     { "LD_E_L",     4,  &E,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_E_HL] =    { "LD_E_HL",    8,  &E,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_H_A] =     { "LD_H_A",     4,  &H,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_B] =     { "LD_H_B",     4,  &H,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_C] =     { "LD_H_C",     4,  &H,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_D] =     { "LD_H_D",     4,  &H,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_E] =     { "LD_H_E",     4,  &H,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_H] =     { "LD_H_H",     4 , &H,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_L] =     { "LD_H_L",     4,  &H,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_H_HL]  =   { "LD_H_HL",    8,  &H,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_L_A] =     { "LD_L_A",     4,  &L,      &A,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_B]  =    { "LD_L_B",     4,  &L,      &B,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_C] =     { "LD_L_C",     4,  &L,      &C,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_D] =     { "LD_L_D",     4,  &L,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_E] =     { "LD_L_E",     4,  &L,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_H] =     { "LD_L_H",     4,  &L,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_L] =     { "LD_L_L",     4,  &L,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_HL] =    { "LD_L_HL",    8,  &L,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
	instruction_table_map[LD_HL_A] =    { "LD_HL_A",    8,  &H,      &A,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_B] =    { "LD_HL_B",    8,  &H,      &B,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_C] =    { "LD_HL_C",    8,  &H,      &C,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_D] =    { "LD_HL_D",    8,  &H,      &D,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_E] =    { "LD_HL_E",    8,  &H,      &E,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_H] =    { "LD_HL_H",    8,  &H,      &H,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_L] =    { "LD_HL_L",    8,  &H,      &L,      &L,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_HL_n] =    { "LD_HL_n",    12, &H,      nullptr, &L,      nullptr, &CPU::ld_r1r3_n };
	instruction_table_map[LDD_HL_A] =   { "LDD_HL_A",   8,  &H,      &A,      &L,      nullptr, &CPU::ldd_r1r3_r2 };
	instruction_table_map[LDI_HL_A] =   { "LDI_HL_A",   8,  &H,      &A,      &L,      nullptr, &CPU::ldi_r1r3_r2 };
	instruction_table_map[LD_BC_A] =    { "LD_BC_A",    8,  &B,      &A,      &C,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_DE_A] =    { "LD_DE_A",    8,  &D,      &A,      &E,      nullptr, &CPU::ld_r1r3_r2 };
	instruction_table_map[LD_nn_A] =    { "LD_nn_A",    16, &A,      nullptr, nullptr, nullptr, &CPU::ld_nn_r1 };
	instruction_table_map[LDH_n_A] =    { "LDH_n_A",    12, &A,      nullptr, nullptr, nullptr, &CPU::ldh_n_r1 }; 
	instruction_table_map[LD_BC_nn] =   { "LD_BC_nn",   12, &B,      nullptr, &C,      nullptr, &CPU::ld_r1r3_nn };
	instruction_table_map[LD_DE_nn] =   { "LD_DE_nn",   12, &D,      nullptr, &E,      nullptr, &CPU::ld_r1r3_nn };
	instruction_table_map[LD_HL_nn] =   { "LD_HL_nn",   12, &H,      nullptr, &L,      nullptr, &CPU::ld_r1r3_nn };
	instruction_table_map[LD_SP_nn] =   { "LD_SP_nn",   12, nullptr, nullptr, nullptr, nullptr, &CPU::ld_sp_nn };
	instruction_table_map[LD_SP_HL] =   { "LD_SP_HL",   8,  &H,      nullptr, &L,      nullptr, &CPU::ld_sp_r1r3 };
	instruction_table_map[LD_HL_SP_n] = { "LD_HL_SP_n", 12, &H,      nullptr, &L,      nullptr, &CPU::ld_r1r3_sp_n };
	instruction_table_map[LD_nn_SP] =   { "LD_nn_SP",   20, nullptr, nullptr, nullptr, nullptr, &CPU::ld_nn_sp };
	instruction_table_map[PUSH_AF] =    { "PUSH_AF",    16, nullptr, nullptr, nullptr, nullptr, &CPU::push_af };
	instruction_table_map[PUSH_BC] =    { "PUSH_BC",    16, &B,      nullptr, &C,      nullptr, &CPU::push_r1r3 };
	instruction_table_map[PUSH_DE] =    { "PUSH_DE",    16, &D,      nullptr, &E,      nullptr, &CPU::push_r1r3 };
	instruction_table_map[PUSH_HL] =    { "PUSH_HL",    16, &H,      nullptr, &L,      nullptr, &CPU::push_r1r3 };
	instruction_table_map[POP_AF] =     { "POP_AF",     12, nullptr, nullptr, nullptr, nullptr, &CPU::pop_af };
	instruction_table_map[POP_BC] =     { "POP_BC",     12, &B,      nullptr, &C,      nullptr, &CPU::pop_r1r3 };
	instruction_table_map[POP_DE] =     { "POP_DE",     12, &D,      nullptr, &E,      nullptr, &CPU::pop_r1r3 };
	instruction_table_map[POP_HL] =     { "POP_HL",     12, &H,      nullptr, &L,      nullptr, &CPU::pop_r1r3 };
	instruction_table_map[ADD_A_A] =    { "ADD_A_A",    4,  &A,      &A,      nullptr, nullptr, &CPU::add_r1_r2};
	instruction_table_map[ADD_A_B] =    { "ADD_A_B",    4,  &A,      &B,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_C] =    { "ADD_A_C",    4,  &A,      &C,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_D] =    { "ADD_A_D",    4,  &A,      &D,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_E] =    { "ADD_A_E",    4,  &A,      &E,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_H] =    { "ADD_A_H",    4,  &A,      &H,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_L] =    { "ADD_A_L",    4,  &A,      &L,      nullptr, nullptr, &CPU::add_r1_r2 };
	instruction_table_map[ADD_A_HL] =   { "ADD_A_HL",   8,  &A,      &H,      nullptr, &L,      &CPU::add_r1_r2r4 };
	instruction_table_map[ADD_A_n] =    { "ADD_A_n",    8,  &A,      nullptr, nullptr, nullptr, &CPU::add_r1_n };
	instruction_table_map[ADC_A_A] =    { "ADC_A_A",    4,  &A,      &A,      nullptr, nullptr, &CPU::adc_r1_r2};
	instruction_table_map[ADC_A_B] =    { "ADC_A_B",    4,  &A,      &B,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_C] =    { "ADC_A_C",    4,  &A,      &C,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_D] =    { "ADC_A_D",    4,  &A,      &D,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_E] =    { "ADC_A_E",    4,  &A,      &E,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_H] =    { "ADC_A_H",    4,  &A,      &H,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_L] =    { "ADC_A_L",    4,  &A,      &L,      nullptr, nullptr, &CPU::adc_r1_r2 };
	instruction_table_map[ADC_A_HL] =   { "ADC_A_HL",   8,  &A,      &H,      nullptr, &L,      &CPU::adc_r1_r2r4 };
	instruction_table_map[ADC_A_n] =    { "ADC_A_n",    8,  &A,      nullptr, nullptr, nullptr, &CPU::adc_r1_n };
	instruction_table_map[SUB_A] =      { "SUB_A",      4,  &A,      &A,      nullptr, nullptr, &CPU::sub_r1_r2};
	instruction_table_map[SUB_B] =      { "SUB_B",      4,  &A,      &B,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_C] =      { "SUB_C",      4,  &A,      &C,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_D] =      { "SUB_D",      4,  &A,      &D,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_E] =      { "SUB_E",      4,  &A,      &E,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_H] =      { "SUB_H",      4,  &A,      &H,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_L] =      { "SUB_L",      4,  &A,      &L,      nullptr, nullptr, &CPU::sub_r1_r2 };
	instruction_table_map[SUB_HL] =     { "SUB_HL",     8,  &A,      &H,      nullptr, &L,      &CPU::sub_r1_r2r4 };
	instruction_table_map[SUB_n] =      { "SUB_n",      8,  &A,      nullptr, nullptr, nullptr, &CPU::sub_r1_n };
	instruction_table_map[SBC_A_A] =    { "SBC_A_A",    4,  &A,      &A,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_B] =    { "SBC_A_B",    4,  &A,      &B,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_C] =    { "SBC_A_C",    4,  &A,      &C,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_D] =    { "SBC_A_D",    4,  &A,      &D,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_E] =    { "SBC_A_E",    4,  &A,      &E,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_H] =    { "SBC_A_H",    4,  &A,      &H,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_L] =    { "SBC_A_L",    4,  &A,      &L,      nullptr, nullptr, &CPU::sbc_r1_r2 };
	instruction_table_map[SBC_A_HL] =   { "SBC_A_HL",   8,  &A,      &H,      nullptr, &L,      &CPU::sbc_r1_r2r4 };
	instruction_table_map[SBC_A_n] =    { "SBC_A_n",    8,  &A,      nullptr, nullptr, nullptr, &CPU::sbc_r1_n };
	instruction_table_map[AND_A] =      { "AND_A",      4,  &A,      &A,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_B] =      { "AND_B",      4,  &A,      &B,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_C] =      { "AND_C",      4,  &A,      &C,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_D] =      { "AND_D",      4,  &A,      &D,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_E] =      { "AND_E",      4,  &A,      &E,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_H] =      { "AND_H",      4,  &A,      &H,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_L] =      { "AND_L",      4,  &A,      &L,      nullptr, nullptr, &CPU::and_r1_r2 };
	instruction_table_map[AND_HL] =     { "AND_HL",     8,  &A,      &H,      nullptr, &L,      &CPU::and_r1_r2r4 };
	instruction_table_map[AND_n] =      { "AND_n",      8,  &A,      nullptr, nullptr, nullptr, &CPU::and_r1_n };
	instruction_table_map[OR_A] =       { "OR_A",       4,  &A,      &A,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_B] =       { "OR_B",       4,  &A,      &B,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_C] =       { "OR_C",       4,  &A,      &C,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_D] =       { "OR_D",       4,  &A,      &D,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_E] =       { "OR_E",       4,  &A,      &E,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_H] =       { "OR_H",       4,  &A,      &H,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_L] =       { "OR_L",       4,  &A,      &L,      nullptr, nullptr, &CPU::or_r1_r2 };
	instruction_table_map[OR_HL] =      { "OR_HL",      8,  &A,      &H,      nullptr, &L,      &CPU::or_r1_r2r4 };
	instruction_table_map[OR_n] =       { "OR_n",       8,  &A,      nullptr, nullptr, nullptr, &CPU::or_r1_n };
	instruction_table_map[XOR_A] =      { "XOR_A",      4,  &A,      &A,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_B] =      { "XOR_B",      4,  &A,      &B,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_C] =      { "XOR_C",      4,  &A,      &C,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_D] =      { "XOR_D",      4,  &A,      &D,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_E] =      { "XOR_E",      4,  &A,      &E,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_H] =      { "XOR_H",      4,  &A,      &H,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_L] =      { "XOR_L",      4,  &A,      &L,      nullptr, nullptr, &CPU::xor_r1_r2 };
	instruction_table_map[XOR_HL] =     { "XOR_HL",     8,  &A,      &H,      nullptr, &L,      &CPU::xor_r1_r2r4 };
	instruction_table_map[XOR_n] =      { "XOR_n",      8,  &A,      nullptr, nullptr, nullptr, &CPU::xor_r1_n };
	instruction_table_map[CP_A] =       { "CP_A",       4,  &A,      &A,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_B] =       { "CP_B",       4,  &A,      &B,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_C] =       { "CP_C",       4,  &A,      &C,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_D] =       { "CP_D",       4,  &A,      &D,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_E] =       { "CP_E",       4,  &A,      &E,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_H] =       { "CP_H",       4,  &A,      &H,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_L] =       { "CP_L",       4,  &A,      &L,      nullptr, nullptr, &CPU::cp_r1_r2 };
	instruction_table_map[CP_HL] =      { "CP_HL",      8,  &A,      &H,      nullptr, &L,      &CPU::cp_r1_r2r4 };
	instruction_table_map[CP_n] =       { "CP_n",       8,  &A,      nullptr, nullptr, nullptr, &CPU::cp_r1_n };
	instruction_table_map[INC_A] =      { "INC_A",      4,  &A,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_B] =      { "INC_B",      4,  &B,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_C] =      { "INC_C",      4,  &C,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_D] =      { "INC_D",      4,  &D,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_E] =      { "INC_E",      4,  &E,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_H] =      { "INC_H",      4,  &H,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_L] =      { "INC_L",      4,  &L,      nullptr, nullptr, nullptr, &CPU::inc_r1 };
	instruction_table_map[INC_HL_A] =   { "INC_[HL]",   12, nullptr, &H,      nullptr, &L,      &CPU::inc_r2r4 };
	instruction_table_map[DEC_A] =      { "DEC_A",      4,  &A,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_B] =      { "DEC_B",      4,  &B,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_C] =      { "DEC_C",      4,  &C,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_D] =      { "DEC_D",      4,  &D,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_E] =      { "DEC_E",      4,  &E,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_H] =      { "DEC_H",      4,  &H,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_L] =      { "DEC_L",      4,  &L,      nullptr, nullptr, nullptr, &CPU::dec_r1 };
	instruction_table_map[DEC_HL_A] =   { "DEC_[HL]",   12, nullptr, &H,      nullptr, &L,      &CPU::dec_r2r4 };
	instruction_table_map[ADD_HL_BC] =  { "ADD_HL_BC",  8,  &H,      &B,      &L,      &C,      &CPU::add_r1r3_r2r4 };
	instruction_table_map[ADD_HL_DE] =  { "ADD_HL_DE",  8,  &H,      &D,      &L,      &E,      &CPU::add_r1r3_r2r4 };
	instruction_table_map[ADD_HL_HL] =  { "ADD_HL_HL",  8,  &H,      &H,      &L,      &L,      &CPU::add_r1r3_r2r4 };
	instruction_table_map[ADD_HL_SP] =  { "ADD_HL_SP",  8,  &H,      nullptr, &L,      nullptr, &CPU::add_r1r3_sp };
	instruction_table_map[ADD_SP_n] =   { "ADD_SP_n",   16, nullptr, nullptr, nullptr, nullptr, &CPU::add_sp_n };
	instruction_table_map[INC_BC] =     { "INC_BC",     8,  &B,      nullptr, &C,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_DE] =     { "INC_DE",     8,  &D,      nullptr, &E,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_HL] =     { "INC_HL",     8,  &H,      nullptr, &L,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_SP] =     { "INC_SP",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::inc_sp };
	instruction_table_map[DEC_BC] =     { "DEC_BC",     8,  &B,      nullptr, &C,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_DE] =     { "DEC_DE",     8,  &D,      nullptr, &E,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_HL] =     { "DEC_HL",     8,  &H,      nullptr, &L,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_SP] =     { "DEC_SP",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::dec_sp };
	instruction_table_map[DAA] =        { "DAA",        4,  nullptr, nullptr, nullptr, nullptr, &CPU::daa };
	instruction_table_map[CPL] =        { "CPL",        4,  nullptr, nullptr, nullptr, nullptr, &CPU::cpl };
	instruction_table_map[CCF] =        { "CCF",        4,  nullptr, nullptr, nullptr, nullptr, &CPU::ccf };
	instruction_table_map[SCF] =        { "SCF",        4,  nullptr, nullptr, nullptr, nullptr, &CPU::scf };
	instruction_table_map[NOP] =	    { "NOP",        4,  nullptr, nullptr, nullptr, nullptr, &CPU::nop };
	instruction_table_map[HALT] =       { "HALT",       4,  nullptr, nullptr, nullptr, nullptr, &CPU::halt };
	instruction_table_map[STOP] =       { "STOP",       4,  nullptr, nullptr, nullptr, nullptr, &CPU::stop };
	instruction_table_map[DI] =         { "DI",         4,  nullptr, nullptr, nullptr, nullptr, &CPU::di };
	instruction_table_map[EI] =         { "EI",         4,  nullptr, nullptr, nullptr, nullptr, &CPU::ei };
	instruction_table_map[RLCA] =       { "RLCA",       4,  &A,      nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	instruction_table_map[RLA] =        { "RLA",        4,  &A,      nullptr, nullptr, nullptr, &CPU::rl_r1 };
	instruction_table_map[RRCA] =       { "RRCA",       4,  &A,      nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	instruction_table_map[RRA] =        { "RRA",        4,  &A,      nullptr, nullptr, nullptr, &CPU::rr_r1 };
	instruction_table_map[JP_nn] =      { "JP",         16, nullptr, nullptr, nullptr, nullptr, &CPU::jp_nn };
	instruction_table_map[JP_NZ] =      { "JP_NZ",      12, nullptr, nullptr, nullptr, nullptr, &CPU::jp_cc_nn };
	instruction_table_map[JP_Z] =       { "JP_Z",       12, nullptr, nullptr, nullptr, nullptr, &CPU::jp_cc_nn };
	instruction_table_map[JP_NC] =      { "JP_NC",      12, nullptr, nullptr, nullptr, nullptr, &CPU::jp_cc_nn };
	instruction_table_map[JP_C] =       { "JP_C",       12, nullptr, nullptr, nullptr, nullptr, &CPU::jp_cc_nn };
	instruction_table_map[JP_HL] =      { "JP_HL",      4,  &H,      nullptr, &L,      nullptr, &CPU::jp_hl };
	instruction_table_map[JR_n] =       { "JR_n",       12, nullptr, nullptr, nullptr, nullptr, &CPU::jr_n };
	instruction_table_map[JR_NZ] =      { "JR_NZ",      8,  nullptr, nullptr, nullptr, nullptr, &CPU::jr_cc_n };
	instruction_table_map[JR_Z] =       { "JR_Z",       8,  nullptr, nullptr, nullptr, nullptr, &CPU::jr_cc_n };
	instruction_table_map[JR_NC] =      { "JR_NC",      8,  nullptr, nullptr, nullptr, nullptr, &CPU::jr_cc_n };
	instruction_table_map[JR_C] =       { "JR_C",       8,  nullptr, nullptr, nullptr, nullptr, &CPU::jr_cc_n };
	instruction_table_map[CALL_nn] =    { "CALL_nn",    24, nullptr, nullptr, nullptr, nullptr, &CPU::call_nn };
	instruction_table_map[CALL_NZ] =    { "CALL_NZ",    12, nullptr, nullptr, nullptr, nullptr, &CPU::call_cc };
	instruction_table_map[CALL_Z] =     { "CALL_Z",     12, nullptr, nullptr, nullptr, nullptr, &CPU::call_cc };
	instruction_table_map[CALL_NC] =    { "CALL_NC",    12, nullptr, nullptr, nullptr, nullptr, &CPU::call_cc };
	instruction_table_map[CALL_C] =     { "CALL_C",     12, nullptr, nullptr, nullptr, nullptr, &CPU::call_cc };
	instruction_table_map[RST_00] =     { "RST_00",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_08] =     { "RST_08",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_10] =     { "RST_10",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_18] =     { "RST_18",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_20] =     { "RST_20",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_28] =     { "RST_28",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_30] =     { "RST_30",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RST_38] =     { "RST_38",     16, nullptr, nullptr, nullptr, nullptr, &CPU::rst };
	instruction_table_map[RET] =        { "RET",        16, nullptr, nullptr, nullptr, nullptr, &CPU::ret };
	instruction_table_map[RET_NZ] =     { "RET_NZ",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::ret_cc };
	instruction_table_map[RET_Z] =      { "RET_Z",      8,  nullptr, nullptr, nullptr, nullptr, &CPU::ret_cc };
	instruction_table_map[RET_NC] =     { "RET_NC",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::ret_cc };
	instruction_table_map[RET_C] =      { "RET_C",      8,  nullptr, nullptr, nullptr, nullptr, &CPU::ret_cc };
	instruction_table_map[RETI] =       { "RETI",       16, nullptr, nullptr, nullptr, nullptr, &CPU::reti   };
}


// Load the next byte of data to r1 register
void CPU::ld_r1_n()
{
	REG_VAL(one) = bus->read_memory(++PC);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from memory address stored at next 2-bytes of memory to r1 register
void CPU::ld_r1_nn()
{
	uint16_t memory_address = (bus->read_memory(++PC)) | (bus->read_memory(++PC) << 8);
	REG_VAL(one) = bus->read_memory(memory_address);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << "= " << ADDR(memory_address) <<
		        (uint16_t)REG_VAL(one) << "\n";
#endif 
}


// Load data from memory address $FF00 + n to r1 register. $FF00 - $FF7F IO ports range addresses
void CPU::ldh_r1_n()
{
	uint8_t  memory_offset = bus->read_memory(++PC);
	uint16_t memory_address = 0xFF00 + memory_offset;
	REG_VAL(one) = bus->read_memory(memory_address);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = ADDR[0xFF00 + 0x" <<
		        (uint16_t)memory_offset << "] = " << ADDR(memory_address) << "0x" <<
		        (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from r2 to r1 register
void CPU::ld_r1_r2()
{
	REG_VAL(one) = REG_VAL(two);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(two) << " = 0x" << 
		        (uint16_t)REG_VAL(one)  << "\n";
#endif
}


// Load data from memory address stored in 16-bit r2r4 register to r1 register
void CPU::ld_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	REG_VAL(one) = bus->read_memory(memory_address);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << ADDR(memory_address) <<
		        "0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from memory address stored in 16-bit r2r4 register to r1 register and decrement r2r4
void CPU::ldd_r1_r2r4()
{
	ld_r1_r2r4();
	current_instruction.parameter_one = current_instruction.parameter_two;
	current_instruction.parameter_three = current_instruction.parameter_four;
	current_instruction.parameter_two = nullptr;
	current_instruction.parameter_four = nullptr;

#if defined DEBUG_CPU
	log_file << "PC:0x" << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " << 
		        current_instruction.opcode_name; 
#endif

	dec_r1r3();
}


// Load data from memory address stored at 16-bit r2r4 register to r1 register and increment r2r4
void CPU::ldi_r1_r2r4()
{
	ld_r1_r2r4();
	current_instruction.parameter_one = current_instruction.parameter_two;
	current_instruction.parameter_three = current_instruction.parameter_four;
	current_instruction.parameter_two = nullptr;
	current_instruction.parameter_four = nullptr;

#if defined DEBUG_CPU
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		         current_instruction.opcode_name;
#endif

	inc_r1r3();
}


// Load data from r register to memory address stored at 16-bit r1r3 register
void CPU::ld_r1r3_r2()
{
	uint16_t memory_addr = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	bus->write_memory(memory_addr, REG_VAL(two));

#if defined DEBUG_CPU
	log_file << ": " << ADDR(memory_addr) << (uint16_t)REG_VAL(two) << 
		        " = 0x" << (uint16_t)REG_VAL(two) << "\n";
#endif
}


// Load data from r2 register to memory address stored at 16-bit r1r3 register and decrement r1r3
void CPU::ldd_r1r3_r2()
{
	ld_r1r3_r2();

#if defined DEBUG_CPU
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		        current_instruction.opcode_name;
#endif

	dec_r1r3();
}


// Load data from r2 register to memory address stored at 16-bit r1r3 register and increment r1r3
void CPU::ldi_r1r3_r2()
{
	ld_r1r3_r2();

#if defined DEBUG_CPU
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		         current_instruction.opcode_name;
#endif

	inc_r1r3();
}


// Load data from next byte to memory address stored at 16-bit r1r3 register
void CPU::ld_r1r3_n()
{
	uint16_t memory_addr = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint8_t  data = bus->read_memory(++PC);
	bus->write_memory(memory_addr, data);

#if defined DEBUG_CPU
	log_file << ": " << ADDR(memory_addr) << "0x" << (uint16_t)data << "\n";
#endif
}


// Load data from register r1 to memory address stored at next 2-bytes 
void CPU::ld_nn_r1()
{
	uint16_t memory_addr = get_memory_address();
	bus->write_memory(memory_addr, REG_VAL(one));

#if defined DEBUG_CPU
	log_file << ": " << ADDR(memory_addr) << REG_NAME(one) <<
		        " = 0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from r1 register to memory address $FF00 + n. $FF00 - $FF7F IO ports range addresses
void CPU::ldh_n_r1()
{
	uint8_t  address_offset = bus->read_memory(++PC);
	uint16_t memory_address = 0xFF00 + address_offset;
	bus->write_memory(memory_address, REG_VAL(one));

#if defined DEBUG_CPU
	log_file << ": ADDR[0xFF00  + 0x" << (uint16_t)address_offset << "] = " <<
		        ADDR(memory_address) << REG_NAME(one) <<
		        " = 0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from next two bytes of memory to 16-bit r1r3 register
void CPU::ld_r1r3_nn()
{
	REG_VAL(three) = bus->read_memory(++PC);
	REG_VAL(one) = bus->read_memory(++PC);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = 0x" << 
		        combine_two_bytes(REG_VAL(one), REG_VAL(three)) << "\n";
#endif
}


// Load data from next two bytes of memory to 16-bit sp register
void CPU::ld_sp_nn()
{
	SP = get_memory_address();

#if defined DEBUG_CPU
	log_file << ": SP = 0x" << SP << "\n";
#endif
}

// Load data from 16-bit r1r3 register to sp register
void CPU::ld_sp_r1r3()
{
	SP = combine_two_bytes(REG_VAL(one), REG_VAL(three));

#if defined DEBUG_CPU
	log_file << ": SP = " << REG_NAME(one) + REG_NAME(three) << " = 0x" << 
		        SP << "\n";
#endif
}


// Load sp + n to 16-bit r1r3 register
void CPU::ld_r1r3_sp_n()
{
	int8_t byte = bus->read_memory(++PC);
	uint16_t result = SP + byte;
	set_f_register(0, 0, is_half_carry_signed(byte, SP), is_carry_signed(byte, SP));

	REG_VAL(one) = result >> 8;
	REG_VAL(three) = (result << 8) >> 8;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = SP + n = 0x" << 
		        SP << " + 0x" << (((uint16_t)byte) & 0xFF) << " = 0x" << result << 
		        F_REG_BITS << "\n";
#endif
}


// Load data from 16-bit SP register to memory address nn
void CPU::ld_nn_sp()
{
	uint16_t memory_address = get_memory_address();

	bus->write_memory(memory_address, SP & 0x00FF);
	bus->write_memory(++memory_address, (SP & 0xFF00) >> 8);

	
#if defined DEBUG_CPU
	uint16_t memory_address_1 = --memory_address;
	uint16_t memory_address_2 = ++memory_address;
	log_file << ": " << ADDR(memory_address_1) << "0x" <<
		        (uint16_t)bus->read_memory(memory_address_1) << "(SP_LOW)\n\t\t\t\t " <<
		        ADDR(memory_address_2) << "0x" <<
		        (uint16_t)bus-> read_memory(memory_address_2) << "(SP_HIGH)\n";
#endif
}


// Push AF register to stack
void CPU::push_af()
{
	bus->write_memory(--SP, A.register_value);
	uint8_t f_register = (F.Z << 7) | (F.N << 6) | (F.H << 5) | (F.C << 4);
	bus->write_memory(--SP, f_register);

#if defined DEBUG_CPU
	log_file << ": " << ADDR_SP(SP + 1) << "A = 0x" << (uint16_t)A.register_value <<
		        "\n\t\t\t\t" << ADDR_SP(SP) << "F = 0x" << 
		        (uint16_t)f_register << F_REG_BITS << "\n";
#endif
}


// Push r1r3 register to stack
void CPU::push_r1r3()
{
	bus->write_memory(--SP, REG_VAL(one));
	bus->write_memory(--SP, REG_VAL(three));

#if defined DEBUG_CPU
	log_file << ": " << ADDR_SP(SP + 1) << REG_NAME(one) << " = 0x" << (uint16_t)REG_VAL(one) << 
		        "\n\t\t\t\t" << ADDR_SP(SP) << REG_NAME(three) << " = 0x" <<
		        (uint16_t)REG_VAL(three) << "\n";
#endif
}


// Pop AF registers from stack
void CPU::pop_af()
{
	uint8_t f_data = bus->read_memory(SP++);
	set_f_register(f_data & 0x80, f_data & 0x40, f_data & 0x20, f_data & 0x10);

	uint8_t data = bus->read_memory(SP++);
	A.register_value = data;

#if defined DEBUG_CPU
	log_file << ": F = " << ADDR_SP(SP - 2) << "0x" <<  (uint16_t)f_data << 
		        F_REG_BITS  << "\n\t\t\t       A = " << ADDR_SP(SP - 1) <<"0x" << 
		        (uint16_t)A.register_value << "\n";
#endif
}


// Pop 16-bit r1r3 register from stack
void CPU::pop_r1r3()
{
	REG_VAL(three) = bus->read_memory(SP++);
	REG_VAL(one) = bus->read_memory(SP++);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(three) << " = " << ADDR_SP(SP - 2) << "0x" << 
		        (uint16_t)REG_VAL(three) << "\n\t\t\t       " << REG_NAME(one) <<
		        " = " << ADDR_SP(SP - 1) << "0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Add r2 register to r1
void CPU::add_r1_r2()
{
	uint8_t value_one = REG_VAL(one);
	uint8_t value_two = REG_VAL(two);
 	int8_t result = value_one + value_two;
	set_f_register(result == 0, 0, is_half_carry(value_one, value_two), is_carry(value_one, value_two));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " + " << REG_NAME(two) <<
		       " = 0x" << (uint16_t)value_one << " + 0x" << (uint16_t)value_two <<
		       " = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Add data from ADDR[r1r4] to r1 register
void CPU::add_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t data = bus->read_memory(memory_address);
	uint8_t register_value = REG_VAL(one);
	uint8_t result = data + register_value;
	set_f_register(result == 0, 0, is_half_carry(data, register_value), is_carry(data, register_value));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " + "<< ADDR(memory_address) << 
		        "0x" << (uint16_t)register_value << " + 0x" << (uint16_t)data << 
		        " = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Add data from next byte of memory to r1 register
void CPU::add_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	uint8_t register_value = REG_VAL(one);
	uint8_t result = data + register_value;
	set_f_register(result == 0, 0, is_half_carry(data, register_value), is_carry(data, register_value));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) <<
	 	        " + 0x" << (uint16_t)data << " = 0x" << (uint16_t)register_value <<
		        " + 0x" << (uint16_t)data << " = 0x" << (uint16_t)result <<
		        F_REG_BITS << "\n";
#endif
}


// Add (r2 + Carry flag) to r1 register
void CPU::adc_r1_r2()
{	
	uint8_t carry = F.C;
	uint8_t value_one = REG_VAL(one);
	uint8_t value_two = REG_VAL(two);
	uint8_t result = value_one + value_two + carry;
	bool half_carry = is_half_carry(value_one, value_two + carry) || is_half_carry(value_two, carry);
	bool c = is_carry(value_one, value_two + carry) || is_carry(value_two, carry);

	set_f_register(result == 0, 0,
		          ((value_one & 0x0F) + (value_two & 0x0F) + carry) > 0x0F,
		          value_one + value_two + carry > 0xFF);
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " <<  REG_NAME(one) << " = " << REG_NAME(one) << " + " << 
		        REG_NAME(two) << " + F.C = 0x" << (uint16_t)value_one <<
		        " + 0x" << (uint16_t)value_two << " + 0x" << (uint16_t)carry <<
		        " = 0x" <<(uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Add (ADDR[r2r4] + Carry flag) to r1 register
void CPU::adc_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	uint8_t  register_value = REG_VAL(one);
	uint8_t  carry = F.C;
	uint8_t  result = register_value + data + carry;
	set_f_register(result == 0, 0,
		          ((register_value & 0x0F) + (data & 0x0F) + carry) > 0x0F,
		          register_value + data + carry > 0xFF);
	REG_VAL(one) = result;
	
#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(one) << " + " << 
		        ADDR(memory_address) << " + F.C = 0x" <<(uint16_t)register_value << 
		        " + 0x"<< (uint16_t)data << " + 0x" << (uint16_t)carry << 
		        " = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Add (n + Carry flag) to r1 register
void CPU::adc_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	uint8_t carry = F.C;
	uint8_t register_value = REG_VAL(one);
	uint8_t result = register_value + data + carry;
	set_f_register(result == 0, 0, 
		           ((register_value & 0x0F) + (data & 0x0F) + carry) > 0x0F,
		           register_value + data + carry > 0xFF);
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(one) << " + 0x" << 
		        (uint16_t)data << " + F.C = 0x" << (uint16_t)register_value <<
		        " + 0x" << (uint16_t)data << " + 0x" << (uint16_t)carry << " = 0x" << 
		        (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Substract data from r2 register from r1 
void CPU::sub_r1_r2()
{
	uint8_t value_one = REG_VAL(one);
	uint8_t value_two = REG_VAL(two);
	uint8_t result = value_one - value_two;
	set_f_register(result == 0, 1, is_half_borrow(value_one, value_two), is_borrow(value_one, value_two));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " - " << REG_NAME(two) <<
		        " = 0x" << (uint16_t)value_one << " - 0x" << (uint16_t)value_two <<
	  	        " = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Substract data from ADDR[r2r4] data 
void CPU::sub_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t data = bus->read_memory(memory_address);
	uint8_t register_value = REG_VAL(one);
	uint8_t result = register_value - data;
	set_f_register(result == 0, 1, is_half_borrow(register_value, data), is_borrow(register_value, data));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " - " << ADDR(memory_address) <<
		        "0x" << (uint16_t)register_value << " - 0x" << (uint16_t)data <<
		        " = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Substract data from next byte of memory from r1 register
void CPU::sub_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	uint8_t register_value = REG_VAL(one);
	uint8_t result = register_value - data; 
	set_f_register(result == 0, 1, is_half_borrow(register_value, data), is_borrow(register_value, data));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) <<
		        " - 0x" << (uint16_t)data << " = 0x" << (uint16_t)register_value <<
		        " - 0x" << (uint16_t)data << " = 0x" << (uint16_t)result <<
		        F_REG_BITS << "\n";
#endif
}


// Substract (r2 + carry) register from r1
void CPU::sbc_r1_r2()
{
	uint8_t carry = F.C;
	uint8_t value_one = REG_VAL(one);
	uint8_t value_two = REG_VAL(two);
	uint8_t result = value_one - value_two - carry;
	set_f_register(result == 0,
		          1,
		          ((value_one & 0xF) - (value_two & 0xF) - carry) < 0,
		          value_one < (value_two + carry));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(one) << " - (" <<
		        REG_NAME(two) << " + F.C) = 0x" << (uint16_t)value_one <<
		        " - (0x" << (uint16_t)value_two << " + 0x" << (uint16_t)carry <<
		        ") = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Substract (ADDR[r2r4] + Carry) from r1 register
void CPU::sbc_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	uint8_t  register_value = REG_VAL(one);
	uint8_t  carry = F.C;
	uint8_t  result = register_value - (data + carry);
	set_f_register(result == 0, 
		          1,
		          ((register_value & 0xF) - (data & 0xF) - carry) < 0,
		          register_value < (data + carry));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(one) << " - (" << "ADDR[0x" << 
		        memory_address << "]" << " + F.C) = 0x" << (uint16_t)register_value <<
		        " - (0x" << (uint16_t)data << " + 0x" << (uint16_t)carry <<
		        ") = 0x" << (uint16_t)result << F_REG_BITS << "\n";
#endif
}


// Substract (n + Carry) from r1 register
void CPU::sbc_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	uint8_t carry = F.C;
	uint8_t register_value = REG_VAL(one);
	uint8_t result = register_value - data - carry;
	set_f_register(result == 0, 1,
		           ((register_value & 0xF) - (data & 0xF) - carry) < 0,
	               register_value < (data + carry));
	REG_VAL(one) = result;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = " << REG_NAME(one) << " - (0x" <<
		        (uint16_t)data << " + F.C) = 0x" << (uint16_t)register_value <<
		        " - (0x" << (uint16_t)data << " + 0x" << (uint16_t)carry << ") = 0x" <<
	         	(uint16_t)result << F_REG_BITS << "\n";
#endif

}


// Bitwise AND r1 r2 registers
void CPU::and_r1_r2()
{
	REG_VAL(one) &= REG_VAL(two);
	set_f_register(REG_VAL(one) == 0, 0, 1, 0);

#if DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " &= "<< REG_NAME(two) << " = 0x" << 
		        (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise AND r1 ADDR[r2r4]
void CPU::and_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t data = bus->read_memory(memory_address);
	REG_VAL(one) &= data;
	set_f_register(REG_VAL(one) == 0, 0, 1, 0);
	
#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " &= " << ADDR(memory_address) <<
		        REG_NAME(one) << " & 0x" << (uint16_t)data << " = 0x" <<
		        (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise AND r1 next byte of memory
void CPU::and_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	REG_VAL(one) &= data;
	set_f_register(REG_VAL(one) == 0, 0, 1, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " &= 0x" << (uint16_t)data << 
		        " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise OR r1 r2
void CPU::or_r1_r2()
{
	REG_VAL(one) |= REG_VAL(two);
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " |= " << REG_NAME(two) << 
		        " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise OR r1 ADDR[r2r4]
void CPU::or_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	REG_VAL(one) |= data;
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " |= " << ADDR(memory_address) <<
		        REG_NAME(one) << " | " << (uint16_t)data << " = 0x" <<
		        (uint16_t)REG_VAL(one)<< F_REG_BITS << "\n";
#endif
}


// Bitwise OR r1 next byte of memory
void CPU::or_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	REG_VAL(one) |= data;
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " |= 0x" << (uint16_t)data <<
		        " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise XOR r1 r2z
void CPU::xor_r1_r2()
{
	REG_VAL(one) ^= REG_VAL(two);
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU 
	log_file << ": " << REG_NAME(one) << " ^= " << REG_NAME(two) <<
		        " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


//Bitwise XOR r1 ADDR[r2r4]
void CPU::xor_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	REG_VAL(one) ^= data;
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " ^= " << ADDR(memory_address) <<
		        REG_NAME(one) << " ^ " << (uint16_t)data << " = 0x" <<
		        (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Bitwise XOR r1 n
void CPU::xor_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	REG_VAL(one) ^= data;
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " ^= 0x" << (uint16_t)data <<
		        " = 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Compare r1 and r2 registers 
void CPU::cp_r1_r2()
{
	uint8_t result = REG_VAL(one) - REG_VAL(two);
	set_f_register(result == 0, 1, is_half_borrow(REG_VAL(one), REG_VAL(two)), REG_VAL(one) < REG_VAL(two));
	
#if defined DEBUG_CPU 
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)REG_VAL(one) << 
		        " " << REG_NAME(two) << " = 0x" << (uint16_t)REG_VAL(two) << 
		        F_REG_BITS << "\n";
#endif
}


// Compare r1 and ADDR[r2r4] 
void CPU::cp_r1_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	uint8_t  result = REG_VAL(one) - data;
	set_f_register(result == 0, 1, is_half_borrow(REG_VAL(one), data), REG_VAL(one) < data);

#if defined DEBUG_CPU
	log_file << ": " << REG_VAL(one) << " = 0x" << (uint16_t)REG_VAL(one) << 
		        ADDR(memory_address) << "0x" << (uint16_t)data << 
		        F_REG_BITS << "\n";
#endif
}


// Compare r1 and next byte of memory 
void CPU::cp_r1_n()
{
	uint8_t data = bus->read_memory(++PC);
	uint8_t register_value = REG_VAL(one);
	uint8_t result = register_value - data;
	set_f_register(result == 0, 1, is_half_borrow(register_value, data), REG_VAL(one) < data);

#if defined DEBUG_CPU
	log_file << ": " << ADDR(PC) << "0x" << (uint16_t)data << F_REG_BITS << "\n";
#endif
}


// Increments r1 register
void CPU::inc_r1()
{
	set_f_register((uint8_t)(REG_VAL(one) + 1) == 0, 0, is_half_carry(REG_VAL(one), 1), F.C);
	REG_VAL(one)++;

#if defined DEBUG_CPU
	log_file << LOG_REG_VALUE_CHANGE(one, REG_VAL(one) - 1) << F_REG_BITS << "\n";
#endif
}


// Increment data at ADDR[r2r4]
void CPU::inc_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	set_f_register((uint8_t)(data + 1) == 0, 0, is_half_carry(data, 1), F.C);
	data++;
	bus->write_memory(memory_address, data);

#if defined DEBUG_CPU
	log_file << LOG_MEM_VALUE_CHANGE(memory_address, data - 1) << F_REG_BITS << "\n";
#endif
}


// Decrement r1 register
void CPU::dec_r1()
{
	set_f_register((uint8_t)(REG_VAL(one) - 1) == 0, 1, is_half_borrow(REG_VAL(one), 1), F.C);
	REG_VAL(one)--;

#if defined DEBUG_CPU
	log_file << LOG_REG_VALUE_CHANGE(one, REG_VAL(one) + 1) << F_REG_BITS << "\n";
#endif
}


// Decrement data at ADDR[r2r4]
void CPU::dec_r2r4()
{
	uint16_t memory_address = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint8_t  data = bus->read_memory(memory_address);
	set_f_register((uint8_t)(data - 1) == 0, 1, is_half_borrow(data, 1), F.C);
	data--;
	bus->write_memory(memory_address, data);

#if defined DEBUG_CPU
	log_file << LOG_MEM_VALUE_CHANGE(memory_address, (uint8_t)(data + 1)) << F_REG_BITS << "\n";
#endif
}


// ADD 16-bit r2r4 register to r1r3 register
void CPU::add_r1r3_r2r4()
{
	uint16_t register_one = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint16_t register_two = combine_two_bytes(REG_VAL(two), REG_VAL(four));
	uint16_t result = register_one + register_two;
	set_f_register(F.Z, 0, is_half_carry_16_bit(register_one, register_two), is_carry_16_bit(register_one, register_two));
	REG_VAL(one) = result >> 8;
	REG_VAL(three) = result & 0xFF;

#if defined DEBUG_CPU 
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = " << REG_NAME(one) + REG_NAME(three) <<
		        " + " << REG_NAME(two) + REG_NAME(four) << " = 0x" << register_one <<
		        " + 0x" << register_two << " = 0x" << result << F_REG_BITS << "\n";
#endif
}

// Add SP register to 16-bit r1r3 register 
void CPU::add_r1r3_sp()
{
	uint16_t register_one = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	uint16_t result = register_one + SP;
	set_f_register(F.Z, 0, is_half_carry_16_bit(register_one, SP), is_carry_16_bit(register_one, SP));

	REG_VAL(one) = result >> 8;
	REG_VAL(three) = result & 0xFF;

#if defined DEBUG_CPU 
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = " << REG_NAME(one) + REG_NAME(three) <<
		        " + SP" << " = 0x" << register_one << " + 0x" << SP << " = 0x" << 
		        result << F_REG_BITS << "\n";
#endif
};

// Load data from address[$FF00 + C] to register A. $FF00 - $FF7F IO ports range addresses  
void CPU::ld_a_c_io()
{
	uint16_t memory_address = 0xFF00 + REG_VAL(two);
	REG_VAL(one) = bus->read_memory(memory_address);

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) << " = ADDR[0xFF00 + " << REG_NAME(two) <<
		        "] = " << ADDR(memory_address) << "0x" << (uint16_t)REG_VAL(one) << "\n";
#endif
}


// Load data from register A to address[$FF00 + C]. $FF00 - $FF7F IO ports range addresses  
void CPU::ld_c_a_io()
{
	uint16_t memory_address = 0xFF00 + REG_VAL(one);
	uint8_t  data = REG_VAL(two);
	bus->write_memory(memory_address, data);

#if defined DEBUG_CPU
	log_file << ": ADDR[0xFF00 + " << REG_NAME(one) <<"] =" << 
		        ADDR(memory_address) << REG_NAME(two) << 
 		        " = 0x" << (uint16_t)data << "\n";
#endif
}


// Add the next byte of memory to SP register
void CPU::add_sp_n()
{
	int8_t byte = bus->read_memory(++PC);
	uint16_t result = SP + byte;
	set_f_register(0, 0, is_half_carry_signed(byte, SP), is_carry_signed(byte, SP));
	
#if defined DEBUG_CPU 
	log_file << ": SP = 0x" << SP << " + 0x" << (((uint16_t)byte) & 0xFF) <<
		        " = 0x" << result << F_REG_BITS << "\n";
#endif

	SP = result;
}


// Increment 16-bit r1r3 register
void CPU::inc_r1r3()
{
	uint16_t register_data = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	register_data++;
	REG_VAL(one) = register_data >> 8;
	REG_VAL(three) = (register_data << 8) >> 8;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = 0x" << 
		        register_data - 1 << " -> 0x" << register_data << "\n";
#endif
}


// Increment SP register
void CPU::inc_sp()
{
	SP++;

#if defined DEBUG_CPU
	log_file << ": SP = 0x" << SP - 1 << " -> 0x" << SP << "\n";
#endif
}


// Decrement 16-bit r1r3 register
void CPU::dec_r1r3()
{
	uint16_t register_data = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	register_data--;
	REG_VAL(one) = register_data >> 8;
	REG_VAL(three) = (register_data << 8) >> 8;

#if defined DEBUG_CPU
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << 
		        " = 0x" << register_data + 1 << " -> 0x" << register_data << "\n";
#endif
}


// Decrement SP register
void CPU::dec_sp()
{
	SP--;

#if defined DEBUG_CPU
	log_file << ": SP = 0x" << SP + 1 << " -> 0x" << SP << "\n";
#endif
}


// Adjusting A register for correct representation of BCD
void CPU::daa()
{
	uint8_t register_value = A.register_value;
	uint8_t correction_value = 0x00;
	bool carry = false;
	if (!F.N)
	{
		if (F.H || ((register_value & 0x0F) > 0x9))
		{
			correction_value |= 0x6;
		}

		if (F.C || register_value > 0x99)
		{
			correction_value |= 0x60;
			carry = true;
		}
		A.register_value += correction_value;
	}
	else
	{
		if (F.H)
		{
			correction_value |= 0x6;
		}

		if (F.C)
		{
			correction_value |= 0x60;
			carry = true;
		}
		A.register_value -= correction_value;
	}

	set_f_register(A.register_value == 0, F.N, 0, carry);
	
#if defined DEBUG_CPU
	log_file << ": A = 0x" <<(uint16_t)register_value << " -> 0x" << (uint16_t)A.register_value <<
		        F_REG_BITS << "\n";
#endif
}


// Complement A register
void CPU::cpl()
{
	A.register_value = ~A.register_value;
	set_f_register(F.Z, 1, 1, F.C);

#if defined DEBUG_CPU
	log_file << ": A = 0x" << (uint16_t)(~A.register_value) << " -> 0x" << (uint16_t)A.register_value <<
		        F_REG_BITS << "\n";
#endif
}


// Complement carry flag 
void CPU::ccf()
{
	set_f_register(F.Z, 0, 0, F.C ? 0 : 1);

#if defined DEBUG_CPU 
	log_file << ": F.C = 0x" << (uint16_t)(F.C ? 0 : 1) << " -> 0x" << (uint16_t)F.C <<
		        F_REG_BITS << "\n";
#endif
}


// Set carry flag
void CPU::scf()
{
	set_f_register(F.Z, 0, 0, 1);

#if defined DEBUG_CPU
	log_file << ": " << F_REG_BITS << "\n";
#endif
}


// No operation
void CPU::nop()
{

#if defined DEBUG_CPU
	log_file << "\n";
#endif
}


// Halt CPU untill interrupt
void CPU::halt()
{
	halted = true;

#if defined DEBUG_CPU
	log_file << "\n";
#endif
}


// Halt CPU & LCD until button pressed
void CPU::stop()
{
	//assert(false); // Implement this later
	halted = true;
	bus->write_memory(DIV, 0x0);

#if defined DEBUG_CPU
	log_file << "\n";
#endif
}


// Disable interrupt
void CPU::di()
{
	IME = false;

#if defined DEBUG_CPU
	log_file << "\n";
#endif
}


// Enable interrupt
void CPU::ei()
{
	IME = true;

#if defined DEBUG_CPU
	log_file << " : IE=0x" << (uint16_t)bus->read_memory(IE) << " IF=0x" << (uint16_t)bus->read_memory(IF) << "\n";
#endif
}


// Jump to address provided in next two bytes of memory
void CPU::jp_nn()
{
	PC = get_memory_address() - 1;

#if defined DEBUG_CPU
	log_file << LOG_JUMP;
#endif
}


// Jump to address provided in next two bytes of memory, if the condition is true
void CPU::jp_cc_nn()
{
	bool jump = check_jump_condition();

	if (jump)
	{
		PC = get_memory_address() - 1;
		current_instruction.number_of_cycles += 4;
    }
	else
	{
		PC += 2;
	}
	
	
#if defined DEBUG_CPU
	log_file << LOG_CONDITIONAL_JUMP;
#endif
}


// Jump at memory address located at HL registers
void CPU::jp_hl()
{
	PC = combine_two_bytes(REG_VAL(one), REG_VAL(three)) - 1;

#if defined DEBUG_CPU
	log_file << LOG_JUMP;
#endif
}


// Add n to current program counter and jump to it
void CPU::jr_n()
{
	int8_t offset = bus->read_memory(PC + 1);
	PC += offset + 2; // adding 2 to include this opcode and its operand
	PC -= 1;

#if defined DEBUG_CPU
	log_file << LOG_JUMP;
#endif
}


// Add n to current program counter and jump to it, if the condition is true
void CPU::jr_cc_n()
{
	bool jump = check_jump_condition();

	if (jump)
	{
		int8_t offset = bus->read_memory(PC + 1);
		PC += offset + 2; // adding 2 to include this opcode and its operand;
		PC -= 1;
		current_instruction.number_of_cycles += 4;
	}
	else
	{
		PC++;
	}

#if defined DEBUG_CPU
	log_file << LOG_CONDITIONAL_JUMP;
#endif
}


// Push current address onto stack and jump to nn address
void CPU::call_nn()
{
	bus->write_memory(--SP, (((PC + 3) & 0xFF00) >> 8));
	bus->write_memory(--SP, (PC + 3) & 0x00FF);
	PC = get_memory_address() - 1;

#if defined DEBUG_CPU
	log_file << ": " << ADDR_SP(SP + 1) <<  " 0x" << (uint16_t)bus->read_memory(SP + 1) << 
		        "\n\t\t\t\t  " << ADDR_SP(SP) << " 0x" << (uint16_t)bus->read_memory(SP) <<
		        "\n\t\t\t\t  JUMP" << LOG_JUMP;
#endif
}


// Push current address onto stack and jump to nn address, if the condition is true
void CPU::call_cc()
{
	bool jump = check_jump_condition();;

	if (jump)
	{
		call_nn();
		current_instruction.number_of_cycles += 12;
	}
	else
	{
		PC += 2;
	}

#if defined DEBUG_CPU
	if (!jump)
	{
		log_file << F_REG_BITS << " : Jump is ignored\n";
	}
#endif
}


// Push current address onto stack and jump to address 0x0000 + n
void CPU::rst()
{
	bus->write_memory(--SP, ((PC + 1) & 0xFF00) >> 8);
	bus->write_memory(--SP, (PC + 1) & 0x00FF);
	uint8_t offset = get_restart_offset();
	PC = 0x0000 + offset - 1;

#if defined DEBUG_CPU
	log_file << ": " << ADDR_SP(SP + 1) << "0x" << (uint16_t)bus->read_memory(SP + 1) <<
                "\n\t\t\t\t  " << ADDR_SP(SP) << " 0x" << (uint16_t)bus->read_memory(SP) <<
		        "\n\t\t\t\t  JUMP" << LOG_JUMP;
#endif
}



// Pop two bytes from the stack and jump to this address
void CPU::ret()
{
	uint16_t memory_address = 0;
	memory_address = bus->read_memory(SP++) | (bus->read_memory(SP++) << 8);
	PC = memory_address - 1;

#if defined DEBUG_CPU
	log_file << LOG_JUMP;
#endif
}


// Pop two bytes from the stack and jump to this address, if condition is true
void CPU::ret_cc()
{
	bool jump = check_jump_condition();

	if (jump)
	{
		current_instruction.number_of_cycles += 12;
		ret();
	}

#if defined DEBUG_CPU
	if (!jump)
	{
		log_file << F_REG_BITS << " : Jump is ignored\n";
	}
#endif
}



// Pop two bytes from the stack and jump to this address, enable interrupts
void CPU::reti()
{
	ret();

#if defined DEBUG_CPU 
	log_file << "\t\t\t  EI";
#endif

	ei();
}

