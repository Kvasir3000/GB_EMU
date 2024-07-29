#define F_REG_BITS                 ": F.Z = " << (uint16_t)F.Z << " F.N = " << (uint16_t)F.N << " F.H = " \
                                   << (uint16_t)F.H << " F.C = " << (uint16_t)F.C

#define ADDR_SP(addr)		       "ADDR[SP] = ADDR[0x" << addr << "] = "
#define ADDR(addr)                 "ADDR[0x" << addr << "] = "

#define REG_NAME(parameter_value)  current_instruction.parameter_##parameter_value->register_name


