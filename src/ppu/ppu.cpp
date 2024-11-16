#include "ppu.h"

PPU::PPU()
{
	scanline_dots = 0;
	current_line = 0;
	current_mode = MODE_2_OAM_SCAN;
	memset(vram, 0, VRAM_HIGH - VRAM_LOW + 1);
	init_window();
	last_frame_time = std::chrono::high_resolution_clock::now();
	frame_duration = std::chrono::milliseconds(16);

#if defined DEBUG_PPU
	init_debug_windows();
#endif
}

void PPU::init_window()
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	if (result < 0)
	{
		std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	window = SDL_CreateWindow("Game Boy", 250, 100, LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "SDL_CreateRenderer failed " << SDL_GetError() << "\n";
		assert(false);
	}
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
				interrupt |= REQUEST_VBLANK_INTERRUPT;
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
				draw_objects();
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
		uint8_t scrolled_y = scy + current_line - 1;
		fetch_tile_map_line(scrolled_y);
		fetch_tile_line();

		uint8_t tile_y_offset = scrolled_y - (scrolled_y / TILE_DIMENSION) * TILE_DIMENSION;
	
		for (uint8_t i = 0; i < LCD_RESOLUTION_X; i++)
		{
			uint8_t scrolled_x = scx + i;
			uint8_t tile_id_x = scrolled_x / TILE_DIMENSION;
			uint8_t tile_x_offset = scrolled_x - (tile_id_x * TILE_DIMENSION);

			TILE     tile = tile_cache[tile_id_x];
			uint16_t pixel_mask = (PIXEL_MASK << 14) >> (tile_x_offset * 2);
			uint16_t bits_offset = ((14 - tile_x_offset * 2));
			uint8_t  pallet_id = (tile.decoded_data[tile_y_offset] & pixel_mask) >> bits_offset;
			frame_buffer[current_line - 1][i] = pallet_id;
		}  
	}
}

void PPU::fetch_tile_map_line(uint8_t line)
{
	uint16_t tile_map_base_address = (lcdc & LCDC_BG_TILE_MAP) ? BG_TILE_MAP_BASE_1 : BG_TILE_MAP_BASE_0;
	uint8_t tile_id_y = line / TILE_DIMENSION;
	uint16_t tile_map_line_address = tile_map_base_address + (tile_id_y * TILE_MAP_DIMENSION);
	for (uint8_t i = 0; i < TILE_MAP_DIMENSION; i++)
	{
		tile_map_cache[i] = vram[(tile_map_line_address + i) - VRAM_LOW];
	}
}

void PPU::fetch_tile_line()
{
	uint16_t tile_address = (lcdc & LCDC_BG_WINDOW_TILE_DATA) ? TILE_DATA_BASE_1 : TILE_DATA_BASE_0;
	for (uint8_t i = 0; i < TILE_MAP_DIMENSION; i++)
	{
		if (lcdc & LCDC_BG_WINDOW_TILE_DATA)
		{
			tile_address = TILE_DATA_BASE_1 + (tile_map_cache[i] * TILE_SIZE);
		}
		else
		{
			uint8_t t = 0x39;
			int8_t t1 = 0x39;
			int8_t offset = (int8_t)tile_map_cache[i];
			tile_address = TILE_DATA_BASE_0 - (offset * TILE_SIZE);
		}

		TILE tile = sample_tile(tile_address);
		decode_tile(tile);
		tile_cache[i] = tile;
	}
}

PPU::TILE PPU::sample_tile(uint16_t memory_address)
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

void PPU::render_tile(SDL_Renderer* renderer, uint16_t column, uint16_t row, uint16_t scaler, TILE tile)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			// Get pixel value from left to right
			uint8_t pallet_id = (tile.decoded_data[i] & (PIXEL_MASK << (2 * j))) >> (2 * j);
			SDL_Color color = get_pallet_color(pallet_id);

			uint8_t x = (column * 8) + 8 - j - 1;
			uint16_t y = (row * 8) + i;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = { x * scaler, y * scaler, scaler, scaler };
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void PPU::render_frame()
{
	auto elaplsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - last_frame_time);

	if (elaplsed_time.count() < 16)
	{
		std::this_thread::sleep_for(frame_duration - elaplsed_time);
	}
	render_frame_buffer();
	
#if defined DEBUG_PPU
	render_vram_debug();
	render_tile_map_debug();
#endif

	last_frame_time = std::chrono::high_resolution_clock::now();
}

void PPU::render_frame_buffer()
{
	for (uint16_t i = 0; i < LCD_RESOLUTION_Y; i++)
	{
		for (uint16_t j = 0; j < LCD_RESOLUTION_X; j++)
		{
			uint8_t pallet_id = frame_buffer[i][j];
			SDL_Color color = get_pallet_color(pallet_id);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = { j * LCD_RESOLUTION_SCALER, i * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER };
			SDL_RenderFillRect(renderer, &rect);
			frame_buffer[i][j] = 0;
		}
	}
	SDL_RenderPresent(renderer);
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

PPU::OBJECT_ATTRIBUTES PPU::sample_object(uint16_t memory_address)
{
	OBJECT_ATTRIBUTES object = { 0 };
	object.y = oam[memory_address++];
	object.x = oam[memory_address++];
	object.tile_id = oam[memory_address++];
	object.attributes = oam[memory_address++];

	return object;
}

void PPU::select_objects()
{
	selected_objects.clear();
	for (uint16_t i = 0; i <= OAM_HIGH - OAM_LOW; i += 4)
	{
		OBJECT_ATTRIBUTES object = sample_object(i);
		int16_t object_y = object.y - 16;
		if (object_y >= 0 && object_y <= LCD_RESOLUTION_Y)
		{
			selected_objects.push_back(object);
		}
	}
}

void PPU::draw_objects()
{
	select_objects();
	for (uint16_t i = 0; i < selected_objects.size(); i++)
	{
		OBJECT_ATTRIBUTES object = selected_objects[i];
		uint16_t tile_addres = TILE_DATA_BASE_1 + (object.tile_id * TILE_SIZE);
		TILE tile = sample_tile(tile_addres);
		decode_tile(tile);
		for (uint8_t j = 0; j < TILE_DIMENSION; j++)
		{
			for (uint8_t k = 0; k < TILE_DIMENSION; k++)
			{
				int16_t x = object.x - 8 + k;
				int16_t y = object.y - 16 + j;
				if (x >= 0 && x <= LCD_RESOLUTION_X && y >= 0 && y <= LCD_RESOLUTION_Y)
				{
					uint16_t line = tile.decoded_data[j];
					uint8_t  shift = (14 - (k * 2));
					uint16_t mask = PIXEL_MASK << shift;
					uint16_t temp1 = line & mask;
					uint8_t  temp2 = temp1 >> shift;
					frame_buffer[y][x] = (tile.decoded_data[j] & (PIXEL_MASK << (14 - (k * 2)))) >> (14 - (k * 2));
				}
			}
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
