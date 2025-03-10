#pragma once 


#define BREAK_PC(pc)  if (PC == pc) {__debugbreak();};

#define F_REG_BITS                 ": F.Z = " << (uint16_t)F.Z << " F.N = " << (uint16_t)F.N << " F.H = " \
                                   << (uint16_t)F.H << " F.C = " << (uint16_t)F.C

#define ADDR_SP(addr)		       "ADDR[SP] = ADDR[0x" << addr << "] = "
#define ADDR(addr)                 "ADDR[0x" << addr << "] = "

#define REG_NAME(parameter_value)  current_instruction.parameter_##parameter_value->register_name

#define LOG_BIT_SHIFT(reg_number, original_value) ": " << REG_NAME(reg_number) << " = 0x" << \
                                                       (uint16_t)original_value << " -> 0x" << (uint16_t)REG_VAL(reg_number) \
                                                       << F_REG_BITS << "\n"

#define LOG_BIT_SHIFT_ADDR(addr, original_value) ": " << ADDR(addr) << "0x" << (uint16_t)original_value \
                                               << " -> 0x" << (uint16_t)bus->read_memory(addr) << F_REG_BITS << "\n"

#define LOG_REG_VALUE_CHANGE(reg_number, original_value) ": " << REG_NAME(reg_number) << " = 0x" << (uint16_t)original_value << \
                                                              " -> 0x" << (uint16_t)REG_VAL(reg_number)


#define LOG_MEM_VALUE_CHANGE(addr, original_value)       ": " << ADDR(addr) << "0x" << (uint16_t)original_value << \
                                                                " -> 0x" << (uint16_t)bus->read_memory(addr)

#define LOG_JUMP                 ": 0x" << PC + 1 << "\n"     
#define LOG_CONDITIONAL_JUMP	 F_REG_BITS; if (jump)  {   log_file << LOG_JUMP; } else { log_file << ": Jump is ignored\n"; }



#define PPU_DEBUG_VRAM_RESOLUTION_X     128
#define PPU_DEBUG_VRAM_RESOLUTION_Y     192
#define PPU_DEBUG_VRAM_GRID_X           16
#define PPU_DEBUG_VRAM_GRID_Y           16
#define PPU_DEBUG_SCALER                2
#define PPU_DEBUG_TILE_MAP_RESOLUTION_X 255 
#define PPU_DEBUG_TILE_MAP_RESOLUTION_Y 510
#define PPU_DEBUG_TILE_MAP_GRID_X       32
#define PPU_DEBUG_TILE_MAP_GRID_Y       32

