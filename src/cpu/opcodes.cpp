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
	instruction_table_map[LD_L_D] =     { "LD_L_D",     4,  &L,      &D,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_E] =     { "LD_L_E",     4,  &L,      &E,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_H] =     { "LD_L_H",     4,  &L,      &H,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_L] =     { "LD_L_L",     4,  &L,      &L,      nullptr, nullptr, &CPU::ld_r1_r2 };
	instruction_table_map[LD_L_HL] =    { "LD_L_HL",    8,  &L,      &H,      nullptr, &L,      &CPU::ld_r1_r2r4 };
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
	instruction_table_map[ADD_SP_n] =   { "ADD_SP_n",   16, nullptr, nullptr, nullptr, nullptr, &CPU::add_sp_n };
	instruction_table_map[INC_BC] =     { "INC_BC",     8,  &B,      nullptr, &C,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_DE] =     { "INC_DE",     8,  &D,      nullptr, &E,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_HL] =     { "INC_HL",     8,  &H,      nullptr, &L,      nullptr, &CPU::inc_r1r3 };
	instruction_table_map[INC_SP] =     { "INC_SP",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::inc_sp };
	instruction_table_map[DEC_BC] =     { "DEC_BC",     8,  &B,      nullptr, &C,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_DE] =     { "DEC_DE",     8,  &D,      nullptr, &E,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_HL] =     { "DEC_HL",     8,  &H,      nullptr, &L,      nullptr, &CPU::dec_r1r3 };
	instruction_table_map[DEC_SP] =     { "DEC_SP",     8,  nullptr, nullptr, nullptr, nullptr, &CPU::dec_sp };
 }

// Load the next byte of data to r1 register
void CPU::ld_r1_n()
{
	current_instruction.parameter_one->register_value = bus->read_from_memory(++PC);

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = 0x" <<
		                (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}

// Load data from memory address stored at next 2-bytes of memory to r1 register
void CPU::ld_r1_nn()
{
	uint16_t memory_addr = (bus->read_from_memory(++PC) << 8) | (bus->read_from_memory(++PC));
	current_instruction.parameter_one->register_value = bus->read_from_memory(memory_addr);

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << "= ADDR[0x" << memory_addr << 
		                "] = 0x" << (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif 
}

// Load data from memory address $FF00 + n to r1 register. $FF00 - $FF7F IO ports range addresses
void CPU::ldh_r1_n()
{
	uint8_t  memory_offset = bus->read_from_memory(++PC);
	uint16_t memory_address = 0xFF00 + memory_offset;
	current_instruction.parameter_one->register_value = bus->read_from_memory(memory_address);

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = ADDR[0xFF00 + 0x" <<
		        (uint16_t)memory_offset << "] = ADDR[0x" << memory_address << "] = 0x" <<
		        (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}

// Load data from r2 to r1 register
void CPU::ld_r1_r2()
{
	current_instruction.parameter_one->register_value = current_instruction.parameter_two->register_value;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = " << 
		                current_instruction.parameter_two->register_name << " = 0x" << 
		                (uint16_t)current_instruction.parameter_one->register_value  << "\n";
#endif
}

// Load data from memory address stored in 16-bit r2r4 register to r1 register
void CPU::ld_r1_r2r4()
{
	uint16_t memory_addr = combine_two_bytes(current_instruction.parameter_two->register_value,
		                                     current_instruction.parameter_four->register_value);
	current_instruction.parameter_one->register_value = bus->read_from_memory(memory_addr);

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name << " = " <<
		                "ADDR[0x" << memory_addr << "] = 0x" << 
						(uint16_t)current_instruction.parameter_one->register_value << "\n";
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

#if defined DEBUG
	log_file << "PC:0x" << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " << 
		        current_instruction.opcode_name; 
#endif

	dec_r1r3();
}

// Load data from memory address stored at 16-bit r2r4 register to r1 register and decrement r2r4
void CPU::ldi_r1_r2r4()
{
	ld_r1_r2r4();
	current_instruction.parameter_one = current_instruction.parameter_two;
	current_instruction.parameter_three = current_instruction.parameter_four;
	current_instruction.parameter_two = nullptr;
	current_instruction.parameter_four = nullptr;

#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		         current_instruction.opcode_name;
#endif

	inc_r1r3();
}

// Load data from r register to memory address stored at 16-bit r1r3 register
void CPU::ld_r1r3_r2()
{
	uint16_t memory_addr = combine_two_bytes(current_instruction.parameter_one->register_value,
		                                     current_instruction.parameter_three->register_value);
	bus->write_to_memory(memory_addr, current_instruction.parameter_two->register_value);

#if defined DEBUG
	log_file << ": ADDR[0x" << memory_addr << "] = " << current_instruction.parameter_two->register_name << 
		        " = 0x" << (uint16_t)current_instruction.parameter_two->register_value << "\n";
#endif
}

// Load data from r2 register to memory address stored at 16-bit r1r3 register and decrement r1r3
void CPU::ldd_r1r3_r2()
{
	ld_r1r3_r2();

#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		        current_instruction.opcode_name;
#endif

	dec_r1r3();
}

// Load data from r2 register to memory address stored at 16-bit r1r3 register and increment r1r3
void CPU::ldi_r1r3_r2()
{
	ld_r1r3_r2();

#if defined DEBUG
	log_file << "PC:0x" << std::hex << PC << "-> INST:0x" << (uint16_t)current_opcode << "-> " <<
		         current_instruction.opcode_name;
#endif

	inc_r1r3();
}

// Load data from next byte to memory address stored at 16-bit r1r3 register
void CPU::ld_r1r3_n()
{
	uint16_t memory_addr = combine_two_bytes(current_instruction.parameter_one->register_value,
		                                     current_instruction.parameter_three->register_value);
	uint8_t  data = bus->read_from_memory(++PC);
	bus->write_to_memory(memory_addr, data);

#if defined DEBUG
	log_file << ": ADDR[0x" << memory_addr << "] = " << (uint16_t)data << "\n";
#endif
}

// Load data from register r1 to memory address stored at next 2-bytes 
void CPU::ld_nn_r1()
{
	uint8_t data = current_instruction.parameter_one->register_value;
	uint16_t memory_addr = (bus->read_from_memory(++PC)) | (bus->read_from_memory(++PC) << 8);
	bus->write_to_memory(memory_addr, data);

#if defined DEBUG
	log_file << ": ADDR[0x" << memory_addr << "] = " << current_instruction.parameter_one->register_name <<
		        " = 0x" << (uint16_t)data << "\n";
#endif
}

// Load data from r1 register to memory address $FF00 + n. $FF00 - $FF7F IO ports range addresses
void CPU::ldh_n_r1()
{
	uint8_t  address_offset = bus->read_from_memory(++PC);
	uint16_t memory_address = 0xFF00 + address_offset;
	uint8_t  data = current_instruction.parameter_one->register_value;
	bus->write_to_memory(memory_address, data);

#if defined DEBUG
	log_file << ": ADDR[0xFF00  + 0x" << (uint16_t)address_offset << "] = ADDR[0x" <<
		        memory_address << "] = " << current_instruction.parameter_one->register_name <<
		        " = 0x" << (uint16_t)data << "\n";
#endif
}

// Load data from next two bytes of memory to 16-bit r1r3 register
void CPU::ld_r1r3_nn()
{
	uint8_t data_r1 = bus->read_from_memory(++PC);
	uint8_t data_r2 = bus->read_from_memory(++PC);

	current_instruction.parameter_one->register_value = data_r1;
	current_instruction.parameter_three->register_value = data_r2;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name + current_instruction.parameter_three->register_name <<
		        " = 0x" << combine_two_bytes(data_r1, data_r2) << "\n";
#endif
}

// Load data from next two bytes of memory to 16-bit sp register
void CPU::ld_sp_nn()
{
	uint8_t low_byte = bus->read_from_memory(++PC);
	uint8_t high_byte = bus->read_from_memory(++PC);

	SP = combine_two_bytes(high_byte, low_byte);

#if defined DEBUG
	log_file << ": SP = 0x" << SP << "\n";
#endif
}

// Load data from 16-bit r1r3 register to sp register
void CPU::ld_sp_r1r3()
{
	uint16_t data = combine_two_bytes(current_instruction.parameter_one->register_value,
		                              current_instruction.parameter_three->register_value);
	SP = data;

#if defined DEBUG
	log_file << ": SP = " << current_instruction.parameter_one->register_name +
                current_instruction.parameter_three->register_name << " = 0x" << 
		        data << "\n";
#endif
}


// Load sp + n to 16-bit r1r3 register
void CPU::ld_r1r3_sp_n()
{
	int8_t byte = bus->read_from_memory(++PC);
	uint16_t result = SP + byte;
	F.Z = 0;
	F.N = 0;
	F.H = (((byte & 0xF) + (SP & 0xF)) & 0x10) == 0x10;
	F.C = (((byte & 0xFF) + (SP & 0xFF)) & 0x100) == 0x100;

	current_instruction.parameter_one->register_value = result >> 8;
	current_instruction.parameter_three->register_value = (result << 8) >> 8;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name + current_instruction.parameter_three->register_name <<
		        " = SP + n = 0x" << SP << " + 0x" << (((uint16_t)byte) & 0xFF) << " = 0x" << result << 
		        ": F.Z = " << (uint16_t)F.Z << " F.N = " << (uint16_t)F.N << " F.H = " << (uint16_t)F.H <<
		        " F.C = " << (uint16_t)F.C << "\n";
#endif
}


// Load data from 16-bit SP register to memory address nn
void CPU::ld_nn_sp()
{
	uint8_t low_byte = bus->read_from_memory(++PC);
	uint8_t high_byte = bus->read_from_memory(++PC);
	uint16_t memory_address = combine_two_bytes(high_byte, low_byte);

	bus->write_to_memory(memory_address, SP & 0x00FF);
	bus->write_to_memory(++memory_address, (SP & 0xFF00) >> 8);

	
#if defined DEBUG
	uint16_t memory_address_1 = --memory_address;
	uint16_t memory_address_2 = ++memory_address;
	log_file << ": ADDR[0x" << (uint16_t)(memory_address_1) << "] = 0x" <<
		        (uint16_t)bus->read_from_memory(memory_address_1) << "(SP_LOW)\n\t\t\t\t ADDR[" <<
		        "0x" << (uint16_t)(memory_address_2) << "] = 0x" <<
		        (uint16_t)bus-> read_from_memory(memory_address_2) << "(SP_HIGH)\n";
#endif
}


// Push AF register to stack
void CPU::push_af()
{
	bus->write_to_memory(--SP, A.register_value);
	F.H = 1;
	F.Z = 1;
	F.N = 1;
	uint8_t f_register = (F.Z << 7) | (F.N << 6) | (F.H << 5) | (F.C << 4);
	bus->write_to_memory(--SP, f_register);

#if defined DEBUG
	log_file << ": ADDR[SP] = ADDR[0x" << SP + 1 << "] = A = 0x" << (uint16_t)A.register_value <<
		        "\n\t\t\t\tADDR[SP] = ADDR[0x" << SP << "] = F = 0x" << 
		        (uint16_t)f_register << ": F.Z = " << (uint16_t)F.Z <<
		        " F.N = " << (uint16_t)F.N << " F.H = " << (uint16_t)F.H << " F.C = " <<
		        (uint16_t)F.C << "\n"; "\n";
#endif
}


// Push r1r3 register to stack
void CPU::push_r1r3()
{
	bus->write_to_memory(--SP, current_instruction.parameter_one->register_value);
	bus->write_to_memory(--SP, current_instruction.parameter_three->register_value);

#if defined DEBUG
	log_file << ": ADDR[SP] = ADDR[0x" << SP + 1 << "] = " << 
		        current_instruction.parameter_one->register_name << " = 0x" << 
		        (uint16_t)current_instruction.parameter_one->register_value <<
		        "\n\t\t\t\tADDR[SP] = ADDR[0x" << SP << "] = " << 
		        current_instruction.parameter_three->register_name << " = 0x" <<
		        (uint16_t)current_instruction.parameter_three->register_value << "\n";
#endif
}


// Pop AF registers from stack
void CPU::pop_af()
{
	uint8_t f_data = bus->read_from_memory(SP++);
	F = { (uint8_t)(f_data >> 7), (uint8_t)(f_data << 1 >> 7), (uint8_t)(f_data << 2 >> 7), (uint8_t)(f_data << 3 >> 7)};
	uint8_t data = bus->read_from_memory(SP++);
	A.register_value = data;

#if defined DEBUG
	log_file << ": F = ADDR[SP] = ADDR[0x" << SP - 2 << "] = 0x" <<  (uint16_t)f_data << 
		        ": F.Z = " << (uint16_t)F.Z << " F.N = " << (uint16_t)F.N << 
		        " F.H = " << (uint16_t)F.H << " F.C = " << (uint16_t)F.C << 
		        "\n\t\t\t       A = ADDR[SP] = ADDR[0x" << SP - 1 << "] = 0x" << 
		        (uint16_t)A.register_value << "\n";
#endif
}


// Pop 16-bit r1r3 register from stack
void CPU::pop_r1r3()
{
	uint8_t data = bus->read_from_memory(SP++);
	current_instruction.parameter_three->register_value = data;
	data = bus->read_from_memory(SP++);
	current_instruction.parameter_one->register_value = data;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_three->register_name << 
		        " = ADDR[SP] = ADDR[0x" << SP - 2 << "] = 0x" << 
		        (uint16_t)current_instruction.parameter_three->register_value << 
		        "\n\t\t\t       " << current_instruction.parameter_one->register_name << 
		        " = ADDR[SP] = ADDR[0x" << SP - 1 << "] = 0x" << 
		        (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}


// Load data from address[$FF00 + C] to register A. $FF00 - $FF7F IO ports range addresses  
void CPU::ld_a_c_io()
{
	uint16_t memory_address = 0xFF00 + current_instruction.parameter_two->register_value;
	current_instruction.parameter_one->register_value = bus->read_from_memory(memory_address);

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name <<
		        " = ADDR[0xFF00 +  " << current_instruction.parameter_two->register_name <<
		        "] = ADDR[0x" << memory_address << "] = 0x" <<
		        (uint16_t)current_instruction.parameter_one->register_value << "\n";
#endif
}

// Load data from register A to address[$FF00 + C]. $FF00 - $FF7F IO ports range addresses  
void CPU::ld_c_a_io()
{
	uint16_t memory_address = 0xFF00 + current_instruction.parameter_one->register_value;
	uint8_t  data = current_instruction.parameter_two->register_value;
	bus->write_to_memory(memory_address, data);

#if defined DEBUG
	log_file << ": ADDR[0xFF00 +  " << current_instruction.parameter_one->register_name <<"] = ADDR[0x" << 
		        memory_address << "] = " << current_instruction.parameter_two->register_name << 
 		        " = 0x" << (uint16_t)data << "\n";
#endif
}

// Add the next byte of memory to SP register
void CPU::add_sp_n()
{
	int8_t byte = bus->read_from_memory(++PC);
	uint16_t result = SP + byte;
	F.Z = 0;
	F.N = 0;
	F.H = (((byte & 0xF) + (SP & 0xF)) & 0x10) == 0x10; 
	F.C = (((byte & 0xFF) + (SP & 0xFF)) & 0x100) == 0x100; 
	
#if defined DEBUG 
	log_file << ": SP = 0x" << SP << " + 0x" << (((uint16_t)byte) & 0xFF) <<
		        " = 0x" << result << ": F.Z = "<< (uint16_t)F.Z << " F.N = " << 
		        (uint16_t)F.N << " F.H = " << (uint16_t)F.H << " F.C = " << 
		        (uint16_t)F.C << "\n";
#endif

	SP = result;
}

// Increment 16-bit r1r3 register
void CPU::inc_r1r3()
{
	uint16_t register_data = combine_two_bytes(current_instruction.parameter_one->register_value,
		                                       current_instruction.parameter_three->register_value);
	register_data++;
	current_instruction.parameter_one->register_value = register_data >> 8;
	current_instruction.parameter_three->register_value = (register_data << 8) >> 8;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name + current_instruction.parameter_three->register_name <<
		        " = 0x" << register_data - 1 << " -> 0x" << register_data << "\n";
#endif
}

// Increment SP register
void CPU::inc_sp()
{
	SP++;

#if defined DEBUG
	log_file << ": SP = 0x" << SP - 1 << " -> 0x" << SP << "\n";
#endif
}

// Decrement 16-bit r1r3 register
void CPU::dec_r1r3()
{
	uint16_t register_data = combine_two_bytes(current_instruction.parameter_one->register_value,
		                                       current_instruction.parameter_three->register_value);
	register_data--;
	current_instruction.parameter_one->register_value = register_data >> 8;
	current_instruction.parameter_three->register_value = (register_data << 8) >> 8;

#if defined DEBUG
	log_file << ": " << current_instruction.parameter_one->register_name + current_instruction.parameter_three->register_name << 
		        " = 0x" << register_data + 1 << " -> 0x" << register_data << "\n";
#endif
}

// Decrement SP register
void CPU::dec_sp()
{
	SP--;

#if defined DEBUG
	log_file << ": SP = 0x" << SP + 1 << " -> 0x" << SP << "\n";
#endif
}