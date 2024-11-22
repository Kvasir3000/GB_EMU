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

uint8_t BUS::read_memory(uint64_t memory_address)
{
	if (memory_address >= ROM_BANK_00_LOW && memory_address <= ROM_BANK_00_HIGH)
	{
		return cartridge->read_rom_bank0(memory_address);
	}
	else if (memory_address >= ROM_BANK_NN_LOW && memory_address <= ROM_BANK_NN_HIGH)
	{
		return cartridge->read_rom_bank_nn(memory_address - ROM_BANK_NN_LOW);
	}
	else if (memory_address >= VRAM_LOW && memory_address <= VRAM_HIGH)
	{
		return ppu->read_vram(memory_address - VRAM_LOW);
	}
	else if (memory_address >= EXTERNAL_RAM_LOW && memory_address <= EXTERNAL_RAM_HIGH)
	{
		return cartridge->read_ram(memory_address - EXTERNAL_RAM_LOW);
	}
	else if (memory_address >= WRAM_LOW_BANK_0 && memory_address <= WRAM_HIGH_BANK_0)
	{
		return wram[memory_address - WRAM_LOW_BANK_0];
	}
	else if (memory_address >= WRAM_LOW_BANK_1 && memory_address <= WRAM_HIGH_BANK_1)
	{ 
		return wram[memory_address - WRAM_LOW_BANK_0];
	}
	else if (memory_address >= ECHO_RAM_LOW && memory_address <= ECHO_RAM_HIGH)
	{
		return wram[memory_address - WRAM_LOW_BANK_0 - ECHO_RAM_LOW];
	}
	else if (memory_address >= OAM_LOW && memory_address <= OAM_HIGH)
	{
		return ppu->read_oam(memory_address - OAM_LOW);
	}
	else if (memory_address >= UNUSED_LOW && memory_address <= UNUSED_HIGH)
	{
		return 0xFF;
	}
	else if (memory_address == DIV)
	{
		return timers->read_div();
	}
	else if (memory_address == TIMA)
	{
		return timers->read_tima();
	}
	else if (memory_address == TAC)
	{
		return timers->read_tac();
	}
	else if (memory_address == TMA)
	{
		return timers->read_tma();
	}
	else if (memory_address == JOYPAD_INPUT)
	{
		return joypad->read_p1();
	}
	else if (memory_address == SB) 
	{
		return serial_transfer_data;
	}
	else if (memory_address == SC)
	{
		return serial_transfer_control;
	}
	else if (memory_address == IF)
	{
		return interrupt_flag;
	}
	else if (memory_address >= AUDIO_IO_LOW && memory_address <= AUDIO_IO_HIGH)
	{
		return 0xBE;
	}
	else if (memory_address >= WAVE_PATTERN_LOW && memory_address <= WAVE_PATTERN_HIGH)
	{
		return 0xEF;
	}
	//else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	//{
	//	return 0xDE; // delete this
	//}
	else if (memory_address == LCD_LCDC)
	{
		return ppu->read_lcdc();
	}
	else if (memory_address == LCD_STAT)
	{
		return ppu->read_stat();
	}
	else if (memory_address == LCD_SCY)
	{
		return ppu->read_scy();
	}
	else if (memory_address == LCD_SCX)
	{
		return ppu->read_scx();
	}
	else if (memory_address == LCD_LY)
	{
		return ppu->read_ly();
	}
	else if (memory_address == LCD_LYC)
	{
		return ppu->read_lyc();
	}
	else if (memory_address == LCD_BGP)
	{
		return ppu->read_bgp();
	}
	else if (memory_address == LCD_OBP0)
	{
		return ppu->read_obp0();
	}
	else if (memory_address == LCD_OBP1)
	{
		return ppu->read_obp1();
	}
	else if (memory_address == LCD_WY)
	{
		return ppu->read_wy();
	}
	else if (memory_address == LCD_WX)
	{
		return ppu->read_wx();
	}
	else if (memory_address == DISABLE_BOOT_ROM)
	{
		return disable_boot_rom_flag;
	}
	else if (memory_address >= HRAM_LOW && memory_address <= HRAM_HIGH)
	{
		return hram[memory_address - HRAM_LOW];
	}
	else if (memory_address == IE)
	{
		return interrupt_enable;
	}
	else
	{
		//assert(false);
		return 0xF0;
	}
};

void BUS::write_memory(uint64_t memory_address, uint8_t data)
{
	if (memory_address >= ROM_BANK_00_LOW && memory_address <= ROM_BANK_00_HIGH)
	{
		cartridge->write_rom(memory_address, data);
	}
	else if (memory_address >= ROM_BANK_NN_LOW && memory_address <= ROM_BANK_NN_HIGH)
	{
		cartridge->write_rom(memory_address, data);
	}
	else if (memory_address >= VRAM_LOW && memory_address <= VRAM_HIGH)
	{
		ppu->write_vram(memory_address - VRAM_LOW, data);
	}
	else if (memory_address >= EXTERNAL_RAM_LOW && memory_address <= EXTERNAL_RAM_HIGH)
	{
		cartridge->write_ram(memory_address - EXTERNAL_RAM_LOW, data);
	}
	else if (memory_address >= WRAM_LOW_BANK_0 && memory_address <= WRAM_HIGH_BANK_0)
	{
		wram[memory_address - WRAM_LOW_BANK_0] = data;
	}
	else if (memory_address >= WRAM_LOW_BANK_1 && memory_address <= WRAM_HIGH_BANK_1)
	{
		wram[memory_address - WRAM_LOW_BANK_0] = data;
	}
	else if (memory_address >= ECHO_RAM_LOW && memory_address <= ECHO_RAM_HIGH)
	{
		wram[memory_address - WRAM_LOW_BANK_0 - ECHO_RAM_LOW] = data;
	}
	else if (memory_address >= OAM_LOW && memory_address <= OAM_HIGH)
	{
		ppu->write_oam(memory_address - OAM_LOW, data);
	}
	else if (memory_address >= UNUSED_LOW && memory_address <= UNUSED_HIGH)
	{

	}
	else if (memory_address == DIV)
	{
		timers->reset_div();
	}
	else if (memory_address == TIMA)
	{
		timers->write_tima(data);
	}
	else if (memory_address == TAC)
	{
		timers->write_timer_control(data);
	}
	else if (memory_address == TMA)
	{
		timers->write_tma(data);
	}
	else if (memory_address == JOYPAD_INPUT)
	{
		joypad->write_p1(data);
	}
	else if (memory_address == SB)
	{
		serial_transfer_data = data;
	}
	else if (memory_address == SC)
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
	else if (memory_address == IF)
	{
		interrupt_flag = data;
	}
	else if (memory_address >= AUDIO_IO_LOW && memory_address <= AUDIO_IO_HIGH)
	{

	}
	else if (memory_address >= WAVE_PATTERN_LOW && memory_address <= WAVE_PATTERN_HIGH)
	{

	}
	//else if (memory_addr >= LCD_IO_LOW && memory_addr <= LCD_IO_HIGH)
	//{
	//	// delete this
	//}
	else if (memory_address == LCD_LCDC)
	{
		ppu->write_lcdc(data);
	}
	else if (memory_address == LCD_STAT)
	{
		ppu->write_stat(data);
	}
	else if (memory_address == LCD_SCY)
	{
		ppu->write_scy(data);
	}
	else if (memory_address == LCD_SCX)
	{
		ppu->write_scx(data);
	}
	else if (memory_address == LCD_LYC)
	{
		ppu->write_lyc(data);
	}
	else if (memory_address == OAM_DMA)
	{
		uint16_t src_address = data << 8;
		for (uint16_t i = 0; i <= OAM_HIGH - OAM_LOW; i++)
		{
			uint8_t byte = read_memory(i + src_address);
			ppu->write_oam(i, byte);
		}
	}
	else if (memory_address == LCD_BGP)
	{
		 ppu->write_bgp(data);
	}
	else if (memory_address == LCD_OBP0)
	{
		 ppu->write_obp0(data);
    }
	else if (memory_address == LCD_OBP1)
	{
		 ppu->write_obp1(data);
	}
	else if (memory_address == LCD_WY)
	{
		 ppu->write_wy(data);
	}
	else if (memory_address == LCD_WX)
	{
		 ppu->write_wx(data);
	}
	else if (memory_address == DISABLE_BOOT_ROM)
	{
		disable_boot_rom_flag = data;
	}
	else if (memory_address >= HRAM_LOW && memory_address <= HRAM_HIGH)
	{
		hram[memory_address - HRAM_LOW] = data;
	}
	else if (memory_address == IE)
	{
		interrupt_enable = data;;
	}
};