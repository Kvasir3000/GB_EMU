#include "bus.h"

BUS::BUS()
{

}

BUS::BUS(CARTRIDGE* cartridge, TIMERS* timers, PPU* ppu, JOYPAD* joypad)
{
	this->ppu = ppu;
	this->cartridge = cartridge;
	this->timers = timers;
	this->joypad = joypad;

	interrupt_flag = 0xE1;
	interrupt_enable = 0x00;

	size_t size = WRAM_HIGH_BANK_0 - WRAM_LOW_BANK_0 + 1;
	memset(wram, 0, size);
	size = HRAM_HIGH - HRAM_LOW + 1;
	memset(hram, 0, size);
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
		return ppu->read_vram(memory_addr - VRAM_LOW);
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
		return ppu->read_oam(memory_addr - OAM_LOW);
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
		return joypad->read_p1();
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
	//else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	//{
	//	return 0xDE; // delete this
	//}
	else if (memory_addr == LCD_LCDC)
	{
		return ppu->read_lcdc();
	}
	else if (memory_addr == LCD_SCY)
	{
		return ppu->read_scy();
	}
	else if (memory_addr == LCD_SCX)
	{
		return ppu->read_scx();
	}
	else if (memory_addr == LCD_LY)
	{
		return ppu->read_ly();
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
		//assert(false);
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
		ppu->write_vram(memory_addr - VRAM_LOW, data);
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
		ppu->write_oam(memory_addr - OAM_LOW, data);
	}
	else if (memory_addr >= UNUSED_LOW && memory_addr <= UNUSED_HIGH)
	{

	}
	else if (memory_addr == DIV)
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
		joypad->write_p1(data);
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
	//else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	//{
	//	// delete this
	//}
	else if (memory_addr == LCD_LCDC)
	{
		ppu->write_lcdc(data);
	}
	else if (memory_addr == LCD_SCY)
	{
		ppu->write_scy(data);
	}
	else if (memory_addr == LCD_SCX)
	{
		ppu->write_scx(data);
	}
	else if (memory_addr == OAM_DMA)
	{
		uint16_t src_address = data << 8;
		for (uint16_t i = 0; i <= OAM_HIGH - OAM_LOW; i++)
		{
			uint8_t byte = read_memory(i + src_address);
			ppu->write_oam(i, byte);
		}
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