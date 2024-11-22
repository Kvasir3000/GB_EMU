#include "ppu.h"


void PPU::fetch_tile_map_line(uint8_t line, uint16_t tile_map_base_address)
{
	uint8_t tile_id_y = line / TILE_DIMENSION;
	uint16_t tile_map_line_address = tile_map_base_address + (tile_id_y * TILE_MAP_DIMENSION);
	for (uint8_t i = 0; i < TILE_MAP_DIMENSION; i++)
	{
		tile_map_cache[i] = vram[(tile_map_line_address + i) - VRAM_LOW];
	}
}

void PPU::fetch_tile_line()
{
	uint16_t tile_address;
	for (uint8_t i = 0; i < TILE_MAP_DIMENSION; i++)
	{
		if (lcdc & LCDC_BG_WINDOW_TILE_DATA)
		{
			tile_address = TILE_DATA_BASE_1 + (tile_map_cache[i] * TILE_SIZE);
		}
		else
		{
			tile_address = TILE_DATA_BASE_0 + ((int8_t)tile_map_cache[i] * TILE_SIZE);
		}

		TILE tile = sample_tile(tile_address);
		decode_tile(tile);
		tile_cache[i] = tile;
	}
}

uint8_t PPU::get_pallete(uint8_t tile_id_x, uint8_t tile_x_offset, uint8_t tile_row)
{
	TILE     tile = tile_cache[tile_id_x];
	uint16_t pixel_mask = (PIXEL_MASK << 14) >> (tile_x_offset * 2);
	uint16_t bits_offset = ((14 - tile_x_offset * 2));
	uint8_t  pallete_id = (tile.decoded_data[tile_row] & pixel_mask) >> bits_offset;
	uint8_t  pallete_offset = pallete_id * 2;
	uint8_t  pallete = (bgp & (PIXEL_MASK << pallete_offset)) >> pallete_offset;
    
	return pallete;
}

void PPU::scnaline_background()
{
	if (lcdc & LCDC_BG_WINDOW_ENABLE)
	{
		uint8_t scrolled_y = scy + current_line - 1;
		uint16_t tile_map_base_address = (lcdc & LCDC_BG_TILE_MAP) ? BG_TILE_MAP_BASE_1 : BG_TILE_MAP_BASE_0;
		fetch_tile_map_line(scrolled_y, tile_map_base_address);
		fetch_tile_line();

		uint8_t tile_row = scrolled_y - (scrolled_y / TILE_DIMENSION) * TILE_DIMENSION;

		for (uint8_t i = 0; i < LCD_RESOLUTION_X; i++)
		{
			uint8_t  scrolled_x = scx + i;
			uint8_t  tile_id_x = scrolled_x / TILE_DIMENSION;
			uint8_t  tile_x_offset = scrolled_x - (tile_id_x * TILE_DIMENSION);
			uint8_t  pallete = get_pallete(tile_id_x, tile_x_offset, tile_row);

			frame_buffer[current_line - 1][i] = get_pallet_color(pallete);
		}
	}
}

void PPU::scanline_window()
{
	if (lcdc & LCDC_BG_WINDOW_ENABLE && lcdc & LCDC_WINDOW_ENABLE)
	{
		if (current_line - 1 >= wy)
		{
			uint16_t tile_map_base_address = (lcdc & LCDC_WINDOW_TILE_MAP) ? WINDOW_TILE_MAP_BASE_1 : WINDOW_TILE_MAP_BASE_0;
			fetch_tile_map_line(current_line - 1 - wy, tile_map_base_address);
			fetch_tile_line();
			uint8_t tile_row = current_line - 1 - ((current_line - 1) / TILE_DIMENSION) * TILE_DIMENSION;

			for (uint8_t i = wx + LCD_WINDOW_X_OFFSET; i < LCD_RESOLUTION_X; i++)
			{
				uint8_t  tile_id_x = (i - (wx + LCD_WINDOW_X_OFFSET)) / TILE_DIMENSION;
				uint8_t  tile_x_offset = (i - (wx + LCD_WINDOW_X_OFFSET)) - (tile_id_x * TILE_DIMENSION);
				uint8_t  pallete = get_pallete(tile_id_x, tile_x_offset, tile_row);

				frame_buffer[current_line - 1][i - LCD_WINDOW_X_OFFSET] = get_pallet_color(pallete);
			}
		}
	}
}