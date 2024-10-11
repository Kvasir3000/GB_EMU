#include <iostream>

#include "bus.h"
#include "opcodes.h"
#include "cb_opcodes.h"
#include "common/memory_map_defs.h"


static char dbg_msg[7000] = { 0 };
static int msg_size = 0;

BUS::BUS()
{

}

BUS::BUS(CARTRIDGE* cartridge, TIMERS* timers)
{
	this->cartridge = cartridge;
	this->timers = timers;

	interrupt_flag = 0xE1;
	interrupt_enable = 0x00;
}

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	if (memory_addr >= ROM_BANK_00_LOW && memory_addr <= ROM_BANK_00_HIGH)
	{
		return cartridge->read_rom(memory_addr);
	}
	else if (memory_addr >= ROM_BANK_NN_LOW && memory_addr <= ROM_BANK_NN_HIGH)
	{
		return cartridge->read_rom(memory_addr);
	}
	else if (memory_addr >= VRAM_LOW && memory_addr <= VRAM_HIGH)
	{
		return vram[memory_addr - VRAM_LOW];
	}
	else if (memory_addr >= EXTERNAL_RAM_LOW && memory_addr <= EXTERNAL_RAM_HIGH)
	{
		return cartridge->read_ram(memory_addr);
	}
	else if (memory_addr >= WRAM_LOW_BANK_0 && memory_addr <= WRAM_HIGH_BANK_0)
	{
		return wram[memory_addr - WRAM_LOW_BANK_0];
	}
	else if (memory_addr >= WRAM_LOW_BANK_1 && memory_addr <= WRAM_HIGH_BANK_1)
	{ 
		return wram[memory_addr - WRAM_LOW_BANK_0];
	}
	else if (memory_addr >= ECHO_RAM_LOW && memory_addr <= ECHO_RAM_HIGH)
	{
		return wram[memory_addr - WRAM_LOW_BANK_0 - ECHO_RAM_LOW];
	}
	else if (memory_addr >= OAM_LOW && memory_addr <= OAM_HIGH)
	{
		return oam[memory_addr - OAM_LOW];
	}
	else if (memory_addr >= UNUSED_LOW && memory_addr <= UNUSED_HIGH)
	{
		return 0xFF;
	}
	else if (memory_addr == DIV)
	{
		return timers->read_div();
	}
	else if (memory_addr == TIMA)
	{
		return timers->read_tima();
	}
	else if (memory_addr == TAC)
	{
		return timers->read_tac();
	}
	else if (memory_addr == TMA)
	{
		return timers->read_tma();
	}
	else if (memory_addr == JOYPAD_INPUT)
	{
		return 0xDE;
	}
	else if (memory_addr == SB) 
	{
		return serial_transfer_data;
	}
	else if (memory_addr == SC)
	{
		return serial_transfer_control;
	}
	else if (memory_addr == IF)
	{
		return interrupt_flag;
	}
	else if (memory_addr >= AUDIO_IO_LOW && memory_addr <= AUDIO_IO_HIGH)
	{
		return 0xBE;
	}
	else if (memory_addr >= WAVE_PATTERN_LOW && memory_addr <= WAVE_PATTERN_HIGH)
	{
		return 0xEF;
	}
	else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	{
		return 0xDE;
	}
	else if (memory_addr == DISABLE_BOOT_ROM)
	{
		return disable_boot_rom_flag;
	}
	else if (memory_addr >= HRAM_LOW && memory_addr <= HRAM_HIGH)
	{
		return hram[memory_addr - HRAM_LOW];
	}
	else if (memory_addr == IE)
	{
		return interrupt_enable;
	}
	else
	{
		assert(false);
		return 0xF0;
	}
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	if (memory_addr >= ROM_BANK_00_LOW && memory_addr <= ROM_BANK_00_HIGH)
	{
		cartridge->write_rom(memory_addr, data);
	}
	else if (memory_addr >= ROM_BANK_NN_LOW && memory_addr <= ROM_BANK_NN_HIGH)
	{
		cartridge->write_rom(memory_addr, data);
	}
	else if (memory_addr >= VRAM_LOW && memory_addr <= VRAM_HIGH)
	{
		vram[memory_addr - VRAM_LOW] = data;
	}
	else if (memory_addr >= EXTERNAL_RAM_LOW && memory_addr <= EXTERNAL_RAM_HIGH)
	{
		cartridge->write_ram(memory_addr, data);
	}
	else if (memory_addr >= WRAM_LOW_BANK_0 && memory_addr <= WRAM_HIGH_BANK_0)
	{
		wram[memory_addr - WRAM_LOW_BANK_0] = data;
	}
	else if (memory_addr >= WRAM_LOW_BANK_1 && memory_addr <= WRAM_HIGH_BANK_1)
	{
		wram[memory_addr - WRAM_LOW_BANK_0] = data;
	}
	else if (memory_addr >= ECHO_RAM_LOW && memory_addr <= ECHO_RAM_HIGH)
	{
		wram[memory_addr - WRAM_LOW_BANK_0 - ECHO_RAM_LOW] = data;
	}
	else if (memory_addr >= OAM_LOW && memory_addr <= OAM_HIGH)
	{
		oam[memory_addr - OAM_LOW] = data;
	}
	else if (memory_addr >= UNUSED_LOW && memory_addr <= UNUSED_HIGH)
	{

	}
	if (memory_addr == DIV)
	{
		timers->reset_div();
	}
	else if (memory_addr == TIMA)
	{
		timers->write_tima(data);
	}
	else if (memory_addr == TAC)
	{
		timers->write_timer_control(data);
	}
	else if (memory_addr == TMA)
	{
		timers->write_tma(data);
	}
	else if (memory_addr == JOYPAD_INPUT)
	{

	}
	else if (memory_addr == SB)
	{
		serial_transfer_data = data;
	}
	else if (memory_addr == SC)
	{
		serial_transfer_control = data;

#if defined DEBUG_CPU
		if (serial_transfer_control == 0x81)
		{
			char c = serial_transfer_data;

			dbg_msg[msg_size++] = c;

			serial_transfer_control = 0;
			printf("DBG: %s\n", dbg_msg);
		}
#endif
	}
	else if (memory_addr == IF)
	{
		interrupt_flag = data;
	}
	else if (memory_addr >= AUDIO_IO_LOW && memory_addr <= AUDIO_IO_HIGH)
	{

	}
	else if (memory_addr >= WAVE_PATTERN_LOW && memory_addr <= WAVE_PATTERN_HIGH)
	{

	}
	else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	{

	}
	else if (memory_addr == DISABLE_BOOT_ROM)
	{
		disable_boot_rom_flag = data;
	}
	else if (memory_addr >= HRAM_LOW && memory_addr <= HRAM_HIGH)
	{
		hram[memory_addr - HRAM_LOW] = data;
	}
	else if (memory_addr == IE)
	{
		interrupt_enable = data;;
	}
};