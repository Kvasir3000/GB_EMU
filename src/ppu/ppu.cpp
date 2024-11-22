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
			interrupt |= get_stat_interrupt(LCD_STAT_MODE_0);
			if (lyc == current_line)
			{
				stat |= LCD_STAT_LYC_LY;
				interrupt |= get_stat_interrupt(LCD_STAT_LYX_SELECT);
			}
			else
			{
				stat &= ~LCD_STAT_LYC_LY;
			}
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
	stat = ((stat & 0xF8) >> 2 << 2) | (current_mode);
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
			SDL_Color color = frame_buffer[i][j]; 
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = { j * LCD_RESOLUTION_SCALER, i * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER };
			SDL_RenderFillRect(renderer, &rect);
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
	stat = (data & 0xF8) | (stat & 0x3);
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
