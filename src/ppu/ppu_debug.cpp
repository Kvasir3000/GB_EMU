#include "ppu.h"

#if defined DEBUG_PPU
void PPU::init_debug_windows()
{
	vram_window = SDL_CreateWindow("VRAM", 500, 250, PPU_DEBUG_VRAM_RESOLUTION_X * LCD_RESOLUTION_SCALER,
		                           PPU_DEBUG_VRAM_RESOLUTION_Y * LCD_RESOLUTION_SCALER, SDL_WINDOW_SHOWN);
	if (vram_window < 0)
	{
		std::cout << "SDL_CreateWindow for VRAM debug failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	vram_renderer = SDL_CreateRenderer(vram_window, -1, SDL_RENDERER_ACCELERATED);
	if (vram_renderer < 0)
	{
		std::cout << "SDL_CreateRenderer for VRAM debug failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	tile_map_window = SDL_CreateWindow("TILE MAP", 700, 250, PPU_DEBUG_TILE_MAP_RESOLUTION_X * PPU_DEBUG_SCALER,
		                               PPU_DEBUG_TILE_MAP_RESOLUTION_Y * PPU_DEBUG_SCALER, SDL_WINDOW_SHOWN);
	if (tile_map_window < 0)
	{
		std::cout << "SDL_CreateWindow for TILE MAP debug failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	tile_map_renderer = SDL_CreateRenderer(tile_map_window, -1, SDL_RENDERER_ACCELERATED);
	if (tile_map_renderer < 0)
	{
		std::cout << "SDL_CreateRenderer for TILE MAP debug failed: " << SDL_GetError() << "\n";
		assert(false);
	}
}

void PPU::render_vram_debug()
{
	SDL_SetRenderDrawColor(vram_renderer, 255, 255, 255, 255);
	SDL_RenderClear(vram_renderer);
	for (uint16_t i = 0; i < 24; i++)
	{
		for (uint16_t j = 0; j < 16; j++)
		{
			uint16_t  decoded_tile[8] = { 0 };
			uint16_t  tile_address = TILE_DATA_BASE_1 + (i * TILE_SIZE * 16) + (j * TILE_SIZE);

			TILE tile = sample_tile(tile_address);
			decode_tile(tile);
			render_tile(vram_renderer, j, i, LCD_RESOLUTION_SCALER, tile);
		}
	}
	SDL_SetRenderDrawColor(vram_renderer, 128, 128, 128, 255);

	// Draw VRAM Tile Blocks
	for (uint16_t i = 0; i <= 128; i += 8) 
	{
		SDL_RenderDrawLine(vram_renderer, i * LCD_RESOLUTION_SCALER, 0, i * LCD_RESOLUTION_SCALER, 328 * LCD_RESOLUTION_SCALER);
	}
	for (uint8_t i = 0; i < 200; i += 8)
	{
		SDL_RenderDrawLine(vram_renderer, 0, i * LCD_RESOLUTION_SCALER, 128 * LCD_RESOLUTION_SCALER, i * LCD_RESOLUTION_SCALER);
	}
	SDL_RenderPresent(vram_renderer);
}

void PPU::render_tile_map_debug()
{
	SDL_SetRenderDrawColor(tile_map_renderer, 255, 255, 255, 255);
	SDL_RenderClear(tile_map_renderer);
	for (uint8_t i = 0; i < PPU_DEBUG_TILE_MAP_GRID_Y * 2; i++)
	{
		for (uint8_t j = 0; j < PPU_DEBUG_TILE_MAP_GRID_X; j++)
		{
			uint16_t tile_map_address = WINDOW_TILE_MAP_BASE_0 + (i * PPU_DEBUG_TILE_MAP_GRID_Y) + j;
			uint8_t  tile_id = read_vram(tile_map_address - VRAM_LOW);
			uint16_t tile_address = 0; 
			if (lcdc & LCDC_BG_WINDOW_TILE_DATA)
			{
				tile_address = TILE_DATA_BASE_1 + (tile_id * TILE_SIZE);
			}
			else
			{
				tile_address = TILE_DATA_BASE_0 - ((int8_t)tile_id * TILE_SIZE); // Check this
			}
			
			TILE tile = sample_tile(tile_address);
			decode_tile(tile);
			render_tile(tile_map_renderer, j, i, PPU_DEBUG_SCALER, tile);
		}
	}
	SDL_SetRenderDrawColor(tile_map_renderer, 128, 128, 128, 128);
	// Draw Tile map grid 
	for (uint16_t i = 0; i < PPU_DEBUG_TILE_MAP_RESOLUTION_Y; i += 8)
	{
		SDL_RenderDrawLine(tile_map_renderer, 0, i * PPU_DEBUG_SCALER, PPU_DEBUG_TILE_MAP_RESOLUTION_X * PPU_DEBUG_SCALER, i * PPU_DEBUG_SCALER);
	}

	for (uint16_t i = 0; i < PPU_DEBUG_TILE_MAP_RESOLUTION_X; i += 8)
	{
		SDL_RenderDrawLine(tile_map_renderer, i * PPU_DEBUG_SCALER, 0, i * PPU_DEBUG_SCALER, PPU_DEBUG_TILE_MAP_RESOLUTION_Y * PPU_DEBUG_SCALER);
	}

	render_viewport_debug();
	SDL_RenderPresent(tile_map_renderer);
}

// Only works for tile map 0
void PPU::render_viewport_debug()
{
	uint8_t viewport_y1 = scy;
	uint8_t viewport_x1 = scx;
	uint8_t viewport_y2 = scy + LCD_RESOLUTION_Y;
	uint8_t viewport_x2 = scx + LCD_RESOLUTION_X;

	SDL_SetRenderDrawColor(tile_map_renderer, 255, 0, 0, 255);

	if (viewport_y2 < viewport_y1 && viewport_x2 < viewport_x1)
	{
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x1                                                     * PPU_DEBUG_SCALER, (viewport_y1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_Y / 2 - viewport_y1)) * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, 0           * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, 0           * PPU_DEBUG_SCALER, viewport_x1                                                     * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, (viewport_y1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_Y / 2 - viewport_y1)) * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, (viewport_x1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_X - viewport_x1)) * PPU_DEBUG_SCALER, viewport_y1                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, 0           * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, 0           * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y1                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, (viewport_x1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_X - viewport_x1)) * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
	}
	else if (viewport_y2 < viewport_y1)
	{
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x1 * PPU_DEBUG_SCALER, (viewport_y1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_Y / 2 - viewport_y1)) * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, (viewport_y1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_Y / 2 - viewport_y1)) * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, 0           * PPU_DEBUG_SCALER, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, 0           * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
	    SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1                                                         * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y2                                                         * PPU_DEBUG_SCALER);
	}
	else if (viewport_x2 < viewport_x1)
	{
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x1                                                     * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, (viewport_x1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_X - viewport_x1)) * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, (viewport_x1 + (PPU_DEBUG_TILE_MAP_RESOLUTION_X - viewport_x1)) * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, 0           * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, 0           * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, viewport_x2                                                     * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
	}
	else
	{
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y1 * PPU_DEBUG_SCALER);
		SDL_RenderDrawLine(tile_map_renderer, viewport_x1 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER, viewport_x2 * PPU_DEBUG_SCALER, viewport_y2 * PPU_DEBUG_SCALER);
	}
}
#endif