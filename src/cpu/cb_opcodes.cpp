#include "cpu.h"
#include "assert.h"

void CPU::init_cb_instruction_table()
{
	cb_instruction_table_map[SWAP_A] =  { "SWAP_A",  8,  &A, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_B] =  { "SWAP_B",  8,  &B, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_C] =  { "SWAP_C",  8,  &C, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_D] =  { "SWAP_D",  8,  &D, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_E] =  { "SWAP_E",  8,  &E, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_H] =  { "SWAP_H",  8,  &H, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_L] =  { "SWAP_L",  8,  &L, nullptr, nullptr, nullptr, &CPU::swap_r1 };
	cb_instruction_table_map[SWAP_HL] = { "SWAP_HL", 16, &H, nullptr, &L,      nullptr, &CPU::swap_r1r3 };
	cb_instruction_table_map[RLC_A] =   { "RLC_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_B] =   { "RLC_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_C] =   { "RLC_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_D] =   { "RLC_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_E] =   { "RLC_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_H] =   { "RLC_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_L] =   { "RLC_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::rlc_r1 };
	cb_instruction_table_map[RLC_HL] =  { "RLC_HL",  16, &H, nullptr, &L,      nullptr, &CPU::rlc_r1r3 };
	cb_instruction_table_map[RL_A] =    { "RL_A",    8,  &A, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_B] =    { "RL_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_C] =    { "RL_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_D] =    { "RL_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_E] =    { "RL_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_H] =    { "RL_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_L] =    { "RL_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::rl_r1 };
	cb_instruction_table_map[RL_HL] =   { "RL_D",    16, &H, nullptr, &L,      nullptr, &CPU::rl_r1r3 };
	cb_instruction_table_map[RRC_A] =   { "RRC_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_B] =   { "RRC_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_C] =   { "RRC_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_D] =   { "RRC_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_E] =   { "RRC_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_H] =   { "RRC_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_L] =   { "RRC_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::rrc_r1 };
	cb_instruction_table_map[RRC_HL] =  { "RRC_HL",  16, &H, nullptr, &L,      nullptr, &CPU::rrc_r1r3 };
	cb_instruction_table_map[RR_A] =    { "RR_A",    8,  &A, nullptr, &A,      nullptr, &CPU::rr_r1};
	cb_instruction_table_map[RR_B] =    { "RR_B",    8,  &B, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_C] =    { "RR_C",    8,  &C, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_D] =    { "RR_D",    8,  &D, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_E] =    { "RR_E",    8,  &E, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_H] =    { "RR_H",    8,  &H, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_L] =    { "RR_L",    8,  &L, nullptr, nullptr, nullptr, &CPU::rr_r1 };
	cb_instruction_table_map[RR_HL] =   { "RR_HL",   16, &H, nullptr, &L,      nullptr, &CPU::rr_r1r3 };
	cb_instruction_table_map[SLA_A] =   { "SLA_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_B] =   { "SLA_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_C] =   { "SLA_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::sla_r1 };	
	cb_instruction_table_map[SLA_D] =   { "SLA_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_E] =   { "SLA_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_H] =   { "SLA_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_L] =   { "SLA_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::sla_r1 };
	cb_instruction_table_map[SLA_HL] =  { "SLA_HL",  16, &H, nullptr, &L,      nullptr, &CPU::sla_r1r3 };
	cb_instruction_table_map[SRA_A] =   { "SRA_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_B] =   { "SRA_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_C] =   { "SRA_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_D] =   { "SRA_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_E] =   { "SRA_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_H] =   { "SRA_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_L] =   { "SRA_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::sra_r1 };
	cb_instruction_table_map[SRA_HL] =  { "SRA_HL",  16, &H, nullptr, &L,      nullptr, &CPU::sra_r1r3 };
	cb_instruction_table_map[SRL_A] =   { "SRL_A",   8,  &A, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_B] =   { "SRL_B",   8,  &B, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_C] =   { "SRL_C",   8,  &C, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_D] =   { "SRL_D",   8,  &D, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_E] =   { "SRL_E",   8,  &E, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_H] =   { "SRL_H",   8,  &H, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_L] =   { "SRL_L",   8,  &L, nullptr, nullptr, nullptr, &CPU::srl_r1 };
	cb_instruction_table_map[SRL_HL] =  { "SRL_HL",  16, &H, nullptr, &L,      nullptr, &CPU::srl_r1r3 };
}


// Swap upper and lower nibble of r1 register
void CPU::swap_r1()
{
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) = (register_value << 4) | (register_value >> 4);
	set_f_register(REG_VAL(one) == 0, 0, 0, 0);

#if defined DEBUG
	log_file << ": " << REG_NAME(one) << " = 0x" << (uint16_t)register_value << 
		        " -> 0x" << (uint16_t)REG_VAL(one) << F_REG_BITS << "\n";
#endif
}


// Swap upper and lower bytes of 16-bit r1r3 register
void CPU::swap_r1r3()
{
	uint16_t register_value = combine_two_bytes(REG_VAL(one), REG_VAL(three));
	REG_VAL(one) = register_value & 0x00FF;
	REG_VAL(three) = (register_value & 0xFF00) >> 8;
	set_f_register(combine_two_bytes(REG_VAL(one), REG_VAL(three)), 0, 0, 0);

#if defined DEBUG
	log_file << ": " << REG_NAME(one) + REG_NAME(three) << " = 0x" << register_value <<
		        " -> 0x" << combine_two_bytes(REG_VAL(one), REG_VAL(three)) << 
		        F_REG_BITS << "\n";
#endif
}

// Wrap function for shifting/rotating bits in register
template <typename BIT_OPERATION>
void CPU::register_bit_shift(BIT_OPERATION bit_operation, uint8_t carry_bit)
{
	uint8_t register_value = REG_VAL(one);
	REG_VAL(one) = bit_operation(register_value);
	set_f_register(REG_VAL(one) == 0, 0, 0, register_value & carry_bit);

#if defined DEBUG
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

#if defined DEBUG
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