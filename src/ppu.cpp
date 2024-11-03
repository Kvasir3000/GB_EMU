#include "ppu.h"

PPU::PPU()
{
	scanline_dots = 0;
	current_line = 0;
	current_mode = MODE_2_OAM_SCAN;
	memset(vram, 0, VRAM_HIGH - VRAM_LOW + 1);

#if defined DEBUG_PPU
	init_debug_window();
#endif
}

uint8_t PPU::tick(uint8_t elapsed_dots)
{
	uint8_t interrupt = 0;
	if (!(lcdc & LCDC_LCD_PPU_ENABLE))
	{
		return interrupt;
	}

	for (int i = 0; i < elapsed_dots; i++)
	{
		scanline_dots++;
		if (current_mode == MODE_2_OAM_SCAN && scanline_dots >= MODE_2_OAM_SCAN_DOTS)
		{
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
			current_line++;
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
			if (tile_cache[x_tile_id].raw_data[i] != 0xCD)
			{
				int b = 234;
			}
			if (tile_base_address == TILE_DATA_BASE_1)
			{
				int a = 3;
			}
		    
		}
	}
}

PPU::TILE PPU::sample_tile(uint16_t memory_address )
{
	TILE tile = { 0 };
	for (uint8_t i = 0; i < TILE_SIZE; i++)
	{
		tile.raw_data[i] = read_vram(memory_address++ - VRAM_LOW);
	}
	return tile;
}

void PPU::decode_tile(TILE& tile)
{
	for (uint8_t i = 0; i < TILE_SIZE; i += 2)
	{
		for (uint8_t j = 0; j < TILE_DIMENSION; j++)
		{
			uint8_t lsb = (tile.raw_data[i] & (1 << j)) >> j;
			uint8_t msb = (tile.raw_data[i + 1] & (1 << j)) >> j;
			tile.decoded_data[i / 2] |= ((msb << 1) | lsb) << (2 * j);
		}
	}
}

SDL_Color PPU::get_pallet_color(uint8_t pallet_id)
{
	SDL_Color color = { 0 };
	if (pallet_id == 0)
	{
		color = { 255, 255, 255, 255 };
	}
	else if (pallet_id == 1)
	{
		color = { 128, 128, 128, 255 };
	}
	else if (pallet_id == 2)
	{
		color = { 64, 64, 64, 255 };
	}
	else if (pallet_id == 3)
	{
		color = { 0, 0, 0, 255 };
	}
	return color;
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
	else
	{
		return 0;
	}
}

void PPU::write_vram(uint16_t memory_address, uint8_t data)
{
	if (current_mode != MODE_3_DRAWING_PIXELS)
	{
		vram[memory_address] = data;
	}
	else
	{
		int a = 23;
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

#if defined DEBUG_PPU
	render_vram_debug();
#endif
}