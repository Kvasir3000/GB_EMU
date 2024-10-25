#pragma once

#include <stdint.h>
#include <vector>
#include "common/timers_defs.h"
#include "common/interrupts_defs.h"
#include "cartridge.h"
#include "timers.h"
#include "ppu.h"


class BUS
{
public:
	BUS();
	BUS(CARTRIDGE* cartridge, TIMERS* timers, PPU* ppu);
	uint8_t  read_memory(uint64_t memory_addr);
	void     write_memory(uint64_t memory_addr, uint8_t data);

private:
	 /*
     * For now it stores the memory of the whole system, as I am just implementing CPU at the moment
     * Later on I am planning to add a BUS system implementation with the proper memory mapping
     */
	uint8_t    wram[WRAM_HIGH_BANK_1 - WRAM_LOW_BANK_0 + 1];
	uint8_t    hram[HRAM_HIGH - HRAM_LOW + 1];
	uint8_t    serial_transfer_data;
	uint8_t    serial_transfer_control;
	uint8_t    interrupt_enable;
	uint8_t    interrupt_flag;
	uint8_t    disable_boot_rom_flag;
	PPU*       ppu;
	CARTRIDGE* cartridge;
	TIMERS*    timers;
};
