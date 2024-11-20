#pragma once

// Move this to common header for mbc
#define ROM_SIZE_ADDR                      0x148
#define RAM_SIZE_ADDR                      0x149 
#define ROM_BANK_SIZE_KIB                  16384 
#define RAM_BANK_SIZE_KIB                  8192



#define MBC1_RAM_ENABLE_REGISTER_LOW       0x0000
#define MBC1_RAM_ENABLE_REGISTER_HIGH      0x1FFF
#define MBC1_ROM_BANK_NUMBER_REGISTER_LOW  0x2000
#define MBC1_ROM_BANK_NUMBER_REGISTER_HIGH 0x3FFF
#define MBC1_RAM_BANK_NUMBER_REGISTER_LOW  0x4000
#define MBC1_RAM_BANK_NUMBER_REGISTER_HIGH 0x5FFF
#define MBC1_BANKING_MODE_REGISTER_LOW     0x6000
#define MBC1_BANKING_MODE_REGISTER_HIGH    0x7FFF

#define ENABLE_RAM_BIT_MASK                0x0F
#define ENABLE_RAM                         0xA
#define ROM_BANK_BIT_MASK                  0b11111
#define RAM_BANK_BIT_MASK                  0b11