#include "ppu.h"

PPU::PPU()
{
	scanline_dots = 0;
	current_mode = MODE_2_OAM_SCAN;
}


void PPU::tick(uint8_t elapsed_dots)
{
	for (int i = 0; i < elapsed_dots; i++)
	{
		scanline_dots++;
		if (current_mode == MODE_2_OAM_SCAN && scanline_dots >= MODE_2_OAM_SCAN_DOTS)
		{
			current_mode = MODE_3_DRAWING_PIXELS;
		}
		else if (current_mode == MODE_3_DRAWING_PIXELS && scanline_dots >= MODE_3_DRAWING_PIXELS_DOTS)
		{
			current_mode = MODE_0_HORIZONTAL_BLANK;
		}
		else if (current_mode == MODE_0_HORIZONTAL_BLANK && scanline_dots >= MODE_0_HORIZONTAL_BLANK_DOTS)
		{
			current_mode = MODE_2_OAM_SCAN;
		}
		else if (current_mode == MODE_1_VERTICAL_BLANK && scanline_dots >= MODE_1_VERTICAL_BLANK_DOTS)
		{
			current_mode = MODE_2_OAM_SCAN;
			scanline_dots = 0; 
		}
	}
}

uint8_t PPU::read_oam(uint16_t memory_address)
{
	if (current_mode == MODE_0_HORIZONTAL_BLANK || current_mode == MODE_1_VERTICAL_BLANK)
	{
		return oam[memory_address];
	}
}

void PPU::write_oam(uint16_t memory_address, uint8_t data)
{
	if (current_mode == MODE_0_HORIZONTAL_BLANK || current_mode == MODE_1_VERTICAL_BLANK)
	{
		oam[memory_address] = data;
	}
}

uint8_t PPU::read_vram(uint16_t memory_address)
{
	if (current_mode != MODE_3_DRAWING_PIXELS) 
	{
		return vram[memory_address];
	}
}

void PPU::write_vram(uint16_t memory_address, uint8_t data)
{
	if (current_mode != MODE_3_DRAWING_PIXELS)
	{
		vram[memory_address] = data;
	}
}