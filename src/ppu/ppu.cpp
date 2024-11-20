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
		if (lyc == current_line)
		{
			stat |= LCD_STAT_LYC_LY;
			interrupt |= get_stat_interrupt(LCD_STAT_LYX_SELECT);
		}
		else
		{
			stat &= ~LCD_STAT_LYC_LY;
		}
		
		if (current_mode == MODE_2_OAM_SCAN && scanline_dots >= MODE_2_OAM_SCAN_DOTS)
		{
			scanline_dots = 0;
			current_mode = MODE_3_DRAWING_PIXELS;
		}
		else if (current_mode == MODE_3_DRAWING_PIXELS && scanline_dots >= MODE_3_DRAWING_PIXELS_DOTS)
		{
			scanline_dots = 0;
			current_mode = MODE_0_HORIZONTAL_BLANK;
			interrupt |= get_stat_interrupt(LCD_STAT_MODE_0);
		}
		else if (current_mode == MODE_0_HORIZONTAL_BLANK && scanline_dots >= MODE_0_HORIZONTAL_BLANK_DOTS)
		{
			scanline_dots = 0;
			current_line++;
			if (current_line == LCD_RESOLUTION_Y)
			{
				current_mode = MODE_1_VERTICAL_BLANK;
				interrupt |= REQUEST_VBLANK_INTERRUPT;
				interrupt |= get_stat_interrupt(LCD_STAT_MODE_1);
			}
			else
			{
				scnaline_background();
				scanline_window();
				current_mode = MODE_2_OAM_SCAN;
				interrupt |= get_stat_interrupt(LCD_STAT_MODE_2);
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
				interrupt |= get_stat_interrupt(LCD_STAT_MODE_2);
			}
		}
	}
	return interrupt;
}

uint8_t PPU::get_stat_interrupt(uint8_t condition)
{
	if (stat & condition)
	{
		return REQUEST_LCD_INTERRUPT;
	}
	return 0;
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
			uint8_t scrolled_x = scx + i;
			uint8_t tile_id_x = scrolled_x / TILE_DIMENSION;
			uint8_t tile_x_offset = scrolled_x - (tile_id_x * TILE_DIMENSION);

			TILE     tile = tile_cache[tile_id_x];
			uint16_t pixel_mask = (PIXEL_MASK << 14) >> (tile_x_offset * 2);
			uint16_t bits_offset = ((14 - tile_x_offset * 2));
			uint8_t  pallete_id = (tile.decoded_data[tile_row] & pixel_mask) >> bits_offset;
			uint8_t  pallete_offset = pallete_id * 2;
			uint8_t  pallete = (bgp & (PIXEL_MASK << pallete_offset)) >> pallete_offset;
			frame_buffer[current_line - 1][i].color = get_pallet_color(pallete);
			frame_buffer[current_line - 1][i].pallete_id = pallete_id;
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
				uint8_t tile_id_x = (i - (wx + LCD_WINDOW_X_OFFSET)) / TILE_DIMENSION;
				uint8_t tile_x_offset = (i - (wx + LCD_WINDOW_X_OFFSET)) - (tile_id_x * TILE_DIMENSION);

				TILE     tile = tile_cache[tile_id_x];
				uint16_t pixel_mask = (PIXEL_MASK << 14) >> (tile_x_offset * 2);
				uint16_t bits_offset = ((14 - tile_x_offset * 2));
				uint8_t  pallete_id = (tile.decoded_data[tile_row] & pixel_mask) >> bits_offset;
				uint8_t  pallete_offset = pallete_id * 2;
				uint8_t  pallete = (bgp & (PIXEL_MASK << pallete_offset)) >> pallete_offset;

				frame_buffer[current_line - 1][i - LCD_WINDOW_X_OFFSET].color = get_pallet_color(pallete);
				frame_buffer[current_line - 1][i - LCD_WINDOW_X_OFFSET].pallete_id = pallete_id;
			}
		}
	}
}

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

void PPU::render_frame()
{
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - last_frame_time);

	if (elapsed_time.count() < 16)
	{
		std::this_thread::sleep_for(frame_duration - elapsed_time);
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
			SDL_Color color = frame_buffer[i][j].color; 
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = { j * LCD_RESOLUTION_SCALER, i * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER };
			SDL_RenderFillRect(renderer, &rect);
			frame_buffer[i][j] = { 0, 0, 0, 255 };
		}
	}
	SDL_RenderPresent(renderer);
}

SDL_Color PPU::get_pallet_color(uint8_t pallete_id)
{
	SDL_Color color = { 0 };
	if (pallete_id == 0)
	{
		color = { 232, 252, 204, 255 };
	}
	else if (pallete_id == 1)
	{
		color = { 172, 212, 144, 255 };
	}
	else if (pallete_id == 2)
	{
		color = { 84, 140, 112, 255 };
	}
	else if (pallete_id == 3)
	{
		color = { 20, 44, 56, 255 };
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
	objects.clear();
	for (uint16_t i = 0; i <= OAM_HIGH - OAM_LOW; i += 4)
	{
		OBJECT_ATTRIBUTES object = sample_object(i);
		int16_t object_y = object.y - 16;
		if (object_y >= 0 && object_y <= LCD_RESOLUTION_Y)
		{
			objects.push_back(object);
		}
	}
}

void PPU::sort_object_priority()
{
	std::sort(objects.begin(), objects.end(), [](OBJECT_ATTRIBUTES obj1, OBJECT_ATTRIBUTES obj2) { return (obj1.x > obj2.x); });
}

void PPU::draw_objects()
{
	select_objects();
	sort_object_priority();
	for (uint16_t i = 0; i < objects.size(); i++)
	{
		OBJECT_ATTRIBUTES object = objects[i];
		uint16_t tile_addres = TILE_DATA_BASE_1 + (object.tile_id * TILE_SIZE);
		TILE tile = sample_tile(tile_addres);
		decode_tile(tile);
		draw_object_tile(object, tile);
		if (lcdc & LCDC_OBJ_SIZE)
		{
			tile_addres = TILE_DATA_BASE_1 + ((object.tile_id + 1) * TILE_SIZE);
			tile = sample_tile(tile_addres);
			decode_tile(tile);
			object.y += 8;
			draw_object_tile(object, tile);
		}
	}
}

void PPU::draw_object_tile(OBJECT_ATTRIBUTES object, TILE tile)
{
	for (uint8_t i = 0; i < TILE_DIMENSION; i++)
	{
		for (uint8_t j = 0; j < TILE_DIMENSION; j++)
		{
			int16_t x = object.x - LCD_OBJECT_X_OFFSET + i;
			int16_t y = object.y - LCD_OBJECT_Y_OFFSET + j;
			if (x >= 0 && x <= LCD_RESOLUTION_X && y >= 0 && y <= LCD_RESOLUTION_Y)
			{
				uint8_t tile_column = (object.attributes & OAM_ATTRIBUTES_X_FLIP)? (i * 2) : (14 - (i * 2));
				uint8_t tile_row = (object.attributes & OAM_ATTRIBUTES_Y_FLIP)? TILE_DIMENSION - j - 1 : j;
				uint8_t pallete_id = (tile.decoded_data[tile_row] & (PIXEL_MASK << tile_column)) >> tile_column;

				if (pallete_id != TRANSPERENT_PIXEL)
				{
					uint8_t pallete_offset = pallete_id * 2;
					uint8_t pallete = (((object.attributes & OAM_ATTRIBUTES_DMG_PALLETE) ? obp1 : obp0) & (PIXEL_MASK << pallete_offset)) >> pallete_offset;
					frame_buffer[y][x].color = get_pallet_color(pallete);
				}
			}
		}
	}
}

uint8_t PPU::read_oam(uint16_t memory_address)
{
	return oam[memory_address];
}

void PPU::write_oam(uint16_t memory_address, uint8_t data)
{
	oam[memory_address] = data;
}

uint8_t PPU::read_vram(uint16_t memory_address)
{
	return vram[memory_address];
}

void PPU::write_vram(uint16_t memory_address, uint8_t data)
{
	vram[memory_address] = data;
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

void PPU::write_bgp(uint8_t data)
{
	bgp = data;
}

uint8_t PPU::read_bgp()
{
	return bgp;
}

void PPU::write_obp0(uint8_t data)
{
	obp0 = data;
}

uint8_t PPU::read_obp0()
{
	return obp0;
}

void PPU::write_obp1(uint8_t data)
{
	obp1 = data;
}

uint8_t PPU::read_obp1()
{
	return obp1;
}

void PPU::write_lyc(uint8_t data)
{
	lyc = data;
}

uint8_t PPU::read_lyc()
{
	return lyc;
}

void PPU::write_stat(uint8_t data)
{
	stat = (data & 0xFE) | (stat & 0x3);
}

uint8_t PPU::read_stat()
{
	return stat;
}

void PPU::write_wx(uint8_t data)
{
	wx = data;
}

uint8_t PPU::read_wx()
{
	return wx;
}

void PPU::write_wy(uint8_t data)
{
	wy = data;
}

uint8_t PPU::read_wy()
{
	return wy;
}

uint8_t PPU::read_lcdc()
{
	return lcdc;
}

void PPU::write_lcdc(uint8_t data)
{
	lcdc = data;
}
