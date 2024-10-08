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

BUS::BUS(std::vector<uint8_t> program_data, CARTRIDGE* cartridge, TIMERS* timers)
{
	ram = new uint8_t[0xFFFF + 1];
	uint8_t col = 0;
	uint8_t row = 0;
	this->cartridge = cartridge;
	this->timers = timers;
	memcpy(ram, program_data.data(), program_data.size() * sizeof(uint8_t));

	ram[IF] = 0xE1;
	ram[IE] = 0x00;
};

uint8_t BUS::read_memory(uint64_t memory_addr)
{
	//if (memory_addr >= ROM_BANK_00_LOW && memory_addr <= ROM_BANK_00_HIGH)
	//{
	//	return cartridge->read_rom(memory_addr);
	//}
	//else if (memory_addr >= ROM_BANK_NN_LOW && memory_addr <= ROM_BANK_NN_HIGH)
	//{
	//	return cartridge->read_rom(memory_addr);
	//}
	//else if (memory_addr >= VRAM_LOW && memory_addr <= VRAM_HIGH)
	//{
	//	return vram[memory_addr - VRAM_LOW];
	//}
	//else if (memory_addr >= EXTERNAL_RAM_LOW && memory_addr <= EXTERNAL_RAM_HIGH)
	//{
	//	return cartridge->read_ram(memory_addr);
	//}
	//else if (memory_addr >= WRAM_LOW && memory_addr <= WRAM_HIGH)
	//{
	//	return wram[memory_addr - WRAM_LOW];
	//}
	//else if (memory_addr >= EXTERNAL_WRAM_LOW && memory_addr <= EXTERNAL_WRAM_HIGH)
	//{ 
	//	//TODO: find out how MBC1 treats this 
	//}
	//else if (memory_addr >= ECHO_RAM_LOW && memory_addr <= ECHO_RAM_HIGH)
	//{
	//	return wram[memory_addr - WRAM_LOW - ECHO_RAM_LOW];
	//}
	//else if (memory_addr >= OAM_LOW && memory_addr <= OAM_HIGH)
	//{
	//	return oam[memory_addr - OAM_LOW];
	//}
	//else if (memory_addr >= UNUSED_LOW && memory_addr <= UNUSED_HIGH)
	//{
	//	return 0xFF;
	//}
	//else if (memory_addr == DIV)
	//{
	//	return timers->read_div();
	//}
	//else if (memory_addr == TIMA)
	//{
	//	return timers->read_tima();
	//}
	//else if (memory_addr == TAC)
	//{
	//	return timers->read_tac();
	//}
	////else if (memory_addr >= IO) // Handle IO
	////{

	////}
	//else if (memory_addr >= HRAM_LOW && memory_addr <= HRAM_HIGH)
	//{
	//	return hram[memory_addr - HRAM_LOW];
	//}
	//else
	//{
	//	return ie;
	//}
	//
	return ram[memory_addr];
};

void BUS::write_memory(uint64_t memory_addr, uint8_t data)
{
	if (memory_addr == DIV)
	{
		timers->reset_div();
	}
	else if (memory_addr == TAC)
	{
		timers->write_timer_control(data);
	}
	else
	{
		ram[memory_addr] = data;
		if (memory_addr == SC && ram[SC] == 0x81)
		{
			char c = read_memory(SB);

			dbg_msg[msg_size++] = c;

			write_memory(SC, 0);
			printf("DBG: %s\n", dbg_msg);
		}
	}	
};