#pragma once

#define ROM_BANK_00_LOW      0x0000
#define ROM_BANK_00_HIGH     0x3FFF
#define ROM_BANK_NN_LOW      0x4000
#define ROM_BANK_NN_HIGH     0x7FFF
#define VRAM_LOW             0x8000
#define VRAM_HIGH            0x9FFF
#define EXTERNAL_RAM_LOW     0xA000
#define EXTERNAL_RAM_HIGH    0xBFFF
#define WRAM_LOW_BANK_0      0xC000
#define WRAM_HIGH_BANK_0     0xCFFF
#define WRAM_LOW_BANK_1      0xD000
#define WRAM_HIGH_BANK_1     0xDFFF
#define ECHO_RAM_LOW         0xE000
#define ECHO_RAM_HIGH        0xFDFF
#define OAM_LOW              0xFE00
#define OAM_HIGH             0xFE9F
#define UNUSED_LOW           0xFEA0
#define UNUSED_HIGH          0xFEFF
#define HRAM_LOW             0xFF80
#define HRAM_HIGH            0xFFFE

// IO Ranges
#define JOYPAD_INPUT         0xFF00
#define SB                   0xFF01
#define SC                   0xFF02
#define DIV                  0xFF04
#define TIMA                 0xFF05
#define TMA                  0xFF06
#define TAC                  0xFF07
#define AUDIO_IO_LOW         0xFF10
#define AUDIO_IO_HIGH        0xFF26
#define WAVE_PATTERN_LOW     0xFF30 
#define WAVE_PATTERN_HIGH    0xFF3F
#define LCD_IO_LOW           0xFF40
#define LCD_IO_HIGH          0xFF4B
#define LCD_LCDC             0xFF40
#define LCD_SCY              0xFF42
#define LCD_SCX              0xFF43
#define LCD_LY               0xFF44
#define DISABLE_BOOT_ROM     0xFF05
#define IF                   0xFF0F
#define IE                   0xFFFF

