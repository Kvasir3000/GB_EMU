#include "ppu.h"

PPU::PPU()
{
	scanline_dots = 0;
	current_line = 0;
	current_mode = MODE_2_OAM_SCAN;
}


uint8_t PPU::tick(uint8_t elapsed_dots)
{
	uint8_t interrupt = 0;
	for (int i = 0; i < elapsed_dots; i++)
	{
		scanline_dots++;
		if (current_mode == MODE_2_OAM_SCAN && scanline_dots >= MODE_2_OAM_SCAN_DOTS)
		{
			current_line++;
			scanline_dots = 0;
			current_mode = MODE_3_DRAWING_PIXELS;
		}
		else if (current_mode == MODE_3_DRAWING_PIXELS && scanline_dots >= MODE_3_DRAWING_PIXELS_DOTS)
		{
			scanline_dots = 0;
			current_mode = MODE_0_HORIZONTAL_BLANK;
		}
		else if (current_mode == MODE_0_HORIZONTAL_BLANK && scanline_dots >= MODE_0_HORIZONTAL_BLANK_DOTS)
		{
			scanline_dots = 0;
			if (current_line == LCD_RESOLUTION_Y)
			{
				current_mode = MODE_1_VERTICAL_BLANK;
			}
			else 
			{
				scnaline_background();
				current_mode = MODE_2_OAM_SCAN;
			}
		}
		else if (current_mode == MODE_1_VERTICAL_BLANK && scanline_dots >= MODE_1_VERTICAL_BLANK_DOTS)
		{
			current_line++;
			scanline_dots = 0;
			if (current_line == END_OF_FRAME_SCANLINE)
			{
				render_frame();
				current_mode = MODE_2_OAM_SCAN;
				current_line = 0;
			}
		}
	}
	return interrupt;
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

uint8_t PPU::read_scy()
{
	return scy;
}

void PPU::write_scy(uint8_t data)
{
	scy = data;
}

uint8_t PPU::read_scx()
{
	return scx;
}

void PPU::write_scx(uint8_t data)
{
	scx = data;
}

uint8_t PPU::read_ly() 
{
	return current_line;
}

uint8_t PPU::read_lcdc()
{
	return lcdc;
}

void PPU::write_lcdc(uint8_t data)
{
	lcdc = data;
}

void PPU::render_frame()
{

}

void PPU::scnaline_background()
{
	if (lcdc & LCDC_BG_WINDOW_ENABLE)
	{
		uint8_t viewport_bottom_x = (scx + 159) % 256;
		uint8_t viewport_bottom_y = (scy + 143) % 256;

		uint8_t y_tile_map = scy + current_line;
		fetch_tile_map_line(y_tile_map);
		fetch_tile_line(y_tile_map);
	}
}

void PPU::fetch_tile_map_line(uint8_t y_tile_map)
{
	uint16_t tile_map_base_address = (lcdc & LCDC_BG_TILE_MAP) ? BG_TILE_MAP_BASE_1 : BG_TILE_MAP_BASE_0;
	uint8_t y_tile_id = y_tile_map / TILE_DIMENSION;
	uint16_t tile_map_line_address = tile_map_base_address + (y_tile_id * TILE_MAP_DIMENSION);
	for (uint8_t x_tile_id = 0; x_tile_id < TILE_MAP_DIMENSION; x_tile_id++)
	{
		uint16_t t = (tile_map_line_address + x_tile_id);
		uint16_t t2 = (tile_map_line_address + x_tile_id) - VRAM_LOW;
		tile_map_cache[x_tile_id] = vram[(tile_map_line_address + x_tile_id) - VRAM_LOW];
	}
}

void PPU::fetch_tile_line(uint8_t y_tile_map)
{
	uint16_t tile_base_address = (lcdc & LCDC_BG_WINDOW_TILE_DATA) ? TILE_DATA_BASE_1 : TILE_DATA_BASE_0;

	uint8_t y_offset = y_tile_map - ((y_tile_map / TILE_DIMENSION) * TILE_DIMENSION);
	for (uint8_t x_tile_id = 0; x_tile_id < TILE_MAP_DIMENSION; x_tile_id++)
	{ 
		uint16_t tile_address = (tile_base_address == TILE_DATA_BASE_1) ? tile_base_address + tile_map_cache[x_tile_id] :
			                                                              tile_base_address + (int8_t)tile_map_cache[x_tile_id];
		for (uint8_t i = 0; i < TILE_DIMENSION; i++)
		{
			tile_cache[x_tile_id].raw_data[i] = vram[tile_address - VRAM_LOW];
		}
	}
}
